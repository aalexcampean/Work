//
//  AppMem.swift
//  ExamPractice
//
//  Created by Alex Campean on 2/4/23.
//

import SwiftUI
import RealmSwift
import Network
import Combine

class AppMem: NSObject, ObservableObject {
    @Published var categories = [Category]()
    @Published var tips = [Tip]()
    @Published var easiestTips = [Tip]()
    @Published var errorOccurred = PassthroughSubject<LocalizedError, Never>()
    
    var pending = [() -> Task<(), Never>]()
    
    private var webSocket: URLSessionWebSocketTask!
    
    var connected = false
    var firstConnection = false
    
    
    func refresh() {
        DispatchQueue.main.async {
            Task {
                let realm = try! await Realm()
                
                if self.connected {
                    
                    // FETCH CATEGORIES
                    print("fetching new data...")
                    let url = URL(string: "http://localhost:2302/categories")!
                    let (data, _) = try! await URLSession.shared.data(from: url)
                    
                    try realm.write {
                        let categories = realm.objects(RealmCategory.self)
                        realm.delete(categories)
                    }
                    
                    let dtos = String(decoding:data, as: UTF8.self).dropFirst().dropLast().split(separator: ",")
                    var cats: [CategoryDTO] = []
                    for dto in dtos {
                        let dto = dto.dropFirst().dropLast()
                        let category = CategoryDTO(name: String(dto))
                        cats.append(category)
                    }
                    
                    try realm.write {
                        for cat in cats.enumerated().map({RealmCategory(c: $1, id: $0)}) {
                            realm.add(cat)
                        }
                    }
                    
                    self.categories = cats.enumerated().map { Category(c: $1, id: $0) }
                    
                    
                    
                    // FETCH TIPS
                    try realm.write {
                        let tips = realm.objects(RealmTip.self)
                        realm.delete(tips)
                    }
                    self.tips = []
                    for category in self.categories {
                        let url = URL(string: "http://localhost:2302/tips/\(category.name.replacingOccurrences(of: " ", with: "%20"))")!
                        let (data, _) = try! await URLSession.shared.data(from: url)
                        
                        let dtos = try! JSONDecoder().decode([TipDTO].self, from: data)
                        try realm.write {
                            for dto in dtos.map({ RealmTip(i: $0)}) {
                                realm.add(dto)
                            }
                        }
                        self.tips.append(contentsOf: dtos.map { Tip(i: $0) })
                    }
                    
                    // FETCH EASIEST TIPS
                    let urlEasiest = URL(string: "http://localhost:2302/easiest/")!
                    let (dataE, _) = try! await URLSession.shared.data(from: urlEasiest)
                    
                    let dtosE = try! JSONDecoder().decode([TipDTO].self, from: dataE)
                    self.easiestTips = dtosE.map { Tip(i: $0) }
                    
                    print("finished fetching new data")
                } else {
                    print("loading from local db...")
                    let categories = realm.objects(RealmCategory.self)
                    self.categories = Array(categories.map { Category(c: $0) })
                    
                    let tips = realm.objects(RealmTip.self)
                    self.tips = Array(tips.map { Tip(i: $0) })
                }
            }
        }
    }
    
    func initSocket() {
        let session = URLSession(configuration: .default, delegate: self, delegateQueue: OperationQueue())
        webSocket = session.webSocketTask(with: URL(string: "ws://localhost:2302/")!)
        webSocket.resume()
    }
    
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
                        self.errorOccurred.send("Back online, refreshing...")
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
                    self.errorOccurred.send("No connection, falling back to local db...")
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
    
    func receive() {
        print("ready to receive")
        let workItem = DispatchWorkItem { [weak self] in
            self?.webSocket.receive(completionHandler: { result in
                switch result {
                case .success(let message):
                    switch message {
                    case .data(let data):
                        print("Data received \(data)")
                    case .string(let string):
                        print("String received \(string)")
                        self?.processSocket(message: string)
                    default:
                        break
                    }
                case .failure(let error):
                    print("Error Receiving \(error)")
                }
                self?.receive()
            })
        }
        DispatchQueue.global().asyncAfter(deadline: .now() + 1 , execute: workItem)
    }
    
    func processSocket(message: String) {
        DispatchQueue.main.async { [unowned self] in
            Task {
                let json = try! JSONSerialization.jsonObject(with: message.data(using: .utf8)!) as! [String: Any]
                let data = json as [String: Any]
                errorOccurred.send("Added tip \(data["name"]!) for category \(data["category"]!), difficulty: \(data["difficulty"]!)")
            }
        }
    }
}

extension AppMem: URLSessionWebSocketDelegate {
    func urlSession(_ session: URLSession, webSocketTask: URLSessionWebSocketTask, didOpenWithProtocol protocol: String?) {
        self.receive()
    }
}

