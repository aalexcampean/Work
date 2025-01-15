//
//  Controller.swift
//  GardenningAppExamPractice
//
//  Created by Alex Campean on 2/4/23.
//

import SwiftUI
import RealmSwift
import Network
import Combine

class Controller: NSObject, ObservableObject, URLSessionDelegate {
    // MARK: - Published properties
    @Published var categories: [Category] = []
    @Published var tips: [Tip] = []
    @Published var easiestTips: [Tip] = []
    @Published var errorOccurred = PassthroughSubject<ControllerError, Never>()
    
    // MARK: - Private properties
    private var webSocket: URLSessionWebSocketTask?
    
    // MARK: - Public properties
    var connected = false
    var firstConnection = false
    var pending = [() -> Task<(), Never>]()
    
    // MARK: - Init
    override init() {
        super.init()
        
        let monitor = NWPathMonitor()
        monitor.pathUpdateHandler = { path in
            print("DETECTED NEW NETWORK STATE")
            self.connected = !self.connected;
            if self.connected == (path.status == .satisfied), self.firstConnection {
                return
            }
            print("new network state: \(self.connected)")
            if self.connected {
                if self.firstConnection {
                    DispatchQueue.main.async {
                        self.errorOccurred.send(.backOnline)
                    }
                }
                self.initSocket()
                for operation in self.pending {
                    print("performing pending operation...")
                    _ = operation()
                }
                self.pending = []
            } else {
                DispatchQueue.main.async {
                    self.errorOccurred.send(.noInternet)
                }
            }
            self.refresh()
            if !self.firstConnection {
                self.firstConnection = true
            }
        }
        monitor.start(queue: .init(label: "Network"))
        
        initSocket()
    }
    
    func initSocket() {
        let session = URLSession(configuration: .default, delegate: self, delegateQueue: OperationQueue())
        webSocket = session.webSocketTask(with: URL(string: "ws://localhost:2302/")!)
        webSocket?.resume()
    }
    
    func refresh() {
        DispatchQueue.main.async {
            Task {
                let realm = try! await Realm()
                
                if !self.connected {
                    // fetching local categories
                    let localCategories = realm.objects(LocalStorageCategory.self)
                    self.categories = Array(localCategories.map { Category(category: $0) })
                    
                    // fetching local tips
                    let localTips = realm.objects(LocalStorageTip.self)
                    self.tips = Array(localTips.map { Tip(tip: $0) })
                    
                } else {
                    
                    // deleting old local categories
                    try realm.write {
                        let localCategories = realm.objects(LocalStorageCategory.self)
                        realm.delete(localCategories)
                    }
                    
                    // MARK: - fetching categories from server
                    guard let urlCategories = URL(string: "http://localhost:2302/categories") else {
                        self.errorOccurred.send(.incorrectURL)
                        return
                    }
                    
                    let (data, _) = try await URLSession.shared.data(from: urlCategories)
                    do {
                        let categoryDTOs = try JSONDecoder().decode([CategoryDTO].self, from: data)
                        
                        try realm.write {
                            // adding the newly fetched categories to the local storage
                            for category in categoryDTOs.enumerated().map( {LocalStorageCategory(id: $0, category: $1)} ) {
                                realm.add(category)
                            }
                        }
                        
                        self.categories = categoryDTOs.enumerated().map { Category(id: $0, category: $1) }
                    } catch {
                        self.errorOccurred.send(.internalFailure)
                    }
                    
                    // deleting old local tips
                    try realm.write {
                        let localTips = realm.objects(LocalStorageTip.self)
                        realm.delete(localTips)
                    }
                    self.tips = []
                    
                    // MARK: - fetching tips from server
                    for category in self.categories {
                        guard let urlTips = URL(string: "http://localhost:2302/tips/\(category.name.replacingOccurrences(of: " ", with: "%20"))") else {
                            self.errorOccurred.send(.incorrectURL)
                            return
                        }
                        
                        let (data2, _) = try await URLSession.shared.data(from: urlTips)
                        do {
                            let tipDTOs = try JSONDecoder().decode([TipDTO.Response].self, from: data2)
                            
                            try realm.write {
                                // adding the newly fetched categories to the local storage
                                for category in tipDTOs.map({ LocalStorageTip(tip: $0) }) {
                                    realm.add(category)
                                }
                            }
                            
                            self.tips.append(contentsOf: tipDTOs.map { Tip(tip: $0) })
                        } catch {
                            self.errorOccurred.send(.internalFailure)
                        }
                    }
                    
                    // MARK: - fetching easiest tips from server
                    guard let urlEasiestTips = URL(string: "http://localhost:2302/easiest") else {
                        self.errorOccurred.send(.incorrectURL)
                        return
                    }
                    
                    let (data3, _) = try await URLSession.shared.data(from: urlEasiestTips)
                    do {
                        let tipDTOs = try JSONDecoder().decode([TipDTO.Response].self, from: data3)
                        self.easiestTips = tipDTOs.map { Tip(tip: $0) }
                    } catch {
                        self.errorOccurred.send(.internalFailure)
                    }
                }
            }
        }
    }
    
    func receive() {
        DispatchQueue.global().asyncAfter(deadline: .now() + 1) {
            self.webSocket?.receive { result in
                switch result {
                case .failure(let error):
                    print("Error received: \(error)")
                case .success(let message):
                    switch message {
                    case .string(let string):
                        print("String received: \(string)")
                    case .data(let data):
                        print("Data received: \(data)")
                        DispatchQueue.main.async { [unowned self] in
                            Task {
                                let tipDTO = try JSONDecoder().decode(TipDTO.Response.self, from: data)
                                errorOccurred.send(.controllerError("A new tip has been added: \(tipDTO.name) | Category: \(tipDTO.category) | Difficulty: \(tipDTO.difficulty)"))
                            }
                        }
                    default:
                        break
                    }
                }
            }
            self.receive()
        }
    }
    
    func urlSession(_ session: URLSession, webSocketTask: URLSessionWebSocketTask, didOpenWithProtocol protocol: String?) {
        print("Did connect to soket")
        self.receive()
    }
    
    func urlSession(_ session: URLSession, webSocketTask: URLSessionWebSocketTask, didCloseWith closeCode: URLSessionWebSocketTask.CloseCode, reason: Data?) {
        print("Did close connection with reason")
    }
}
