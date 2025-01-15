//
//  Controller.swift
//  ExamSwift
//
//  Created by Alex Campean on 2/5/23.
//

import SwiftUI
import RealmSwift
import Network
import Combine

class Controller: NSObject, ObservableObject {
    // MARK: - Published properties
    @Published var dates: [Date] = []
    @Published var fitnesProgresses: [FitnessProgress] = []
    @Published var topFitnessProgresses: [FitnessProgress] = []
    @Published var errorOccurred = PassthroughSubject<ControllerError, Never>()
    
    // MARK: - Private properties
    private var webSocket: URLSessionWebSocketTask?
    
    // MARK: - Public properties
    var connected = false
    var firstConnection = false
    var isPending = false
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
            print("---------- Received new network state: \(self.connected)")
            if self.connected {
                if self.firstConnection {
                    DispatchQueue.main.async {
                        self.errorOccurred.send(.backOnline)
                    }
                }
                self.initSocket()
                for operation in self.pending {
                    print("---------- Performing pending operation...")
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
        guard let webSocketURL = URL(string: "ws://localhost:2305/") else {
            self.errorOccurred.send(.incorrectURL)
            return
        }
        webSocket = session.webSocketTask(with: webSocketURL)
        webSocket?.resume()
    }
    
    func refresh() {
        DispatchQueue.main.async {
            Task {
                let realm = try! await Realm()
                
                self.isPending = true
                
                if !self.connected {
                    // fetching local date
                    let localDates = realm.objects(LocalStorageDate.self)
                    self.dates = Array(localDates.map { Date(date: $0) })
                    
                    // fetching local fitness progresses
                    let localFitnessProgresses = realm.objects(LocalStorageFitnessProgress.self)
                    self.fitnesProgresses = Array(localFitnessProgresses.map { FitnessProgress(fitnessProgress: $0) })
                    
                } else {
                    
                    // deleting old local dates
                    try realm.write {
                        let localDates = realm.objects(LocalStorageDate.self)
                        realm.delete(localDates)
                    }
                    
                    // MARK: - fetching dates from server
                    guard let urlDates = URL(string: "http://localhost:2305/dates") else {
                        self.errorOccurred.send(.incorrectURL)
                        return
                    }
                    
                    let (data, _) = try await URLSession.shared.data(from: urlDates)
                    do {
                        let dateDTOs = try JSONDecoder().decode([DateDTO].self, from: data)
                        
                        try realm.write {
                            // adding the newly fetched dates to the local storage
                            for date in dateDTOs.enumerated().map( {LocalStorageDate(id: $0, date: $1)} ) {
                                realm.add(date)
                            }
                        }
                        
                        self.dates = dateDTOs.enumerated().map { Date(id: $0, date: $1) }
                    } catch {
                        self.errorOccurred.send(.internalFailure)
                    }
                    
                    // deleting old local fitness progresses
                    try realm.write {
                        let localFitnessProgresses = realm.objects(LocalStorageFitnessProgress.self)
                        realm.delete(localFitnessProgresses)
                    }
                    self.fitnesProgresses = []
                    
                    // MARK: - fetching fitness progresses from server
                    for date in self.dates {
                        guard let urlFitnessProgresses = URL(string: "http://localhost:2305/entries/\(date.date)") else {
                            self.errorOccurred.send(.incorrectURL)
                            return
                        }
                        
                        let (data2, _) = try await URLSession.shared.data(from: urlFitnessProgresses)
                        do {
                            let fitnessProgressDTOs = try JSONDecoder().decode([FitnessProgressDTO.Response].self, from: data2)
                            
                            try realm.write {
                                // adding the newly fetched fitness progresses to the local storage
                                for fitnessProgress in fitnessProgressDTOs.map({ LocalStorageFitnessProgress(fitnessProgress: $0) }) {
                                    realm.add(fitnessProgress)
                                }
                            }
                            
                            self.fitnesProgresses.append(contentsOf: fitnessProgressDTOs.map { FitnessProgress(fitnessProgress: $0) })
                        } catch {
                            self.errorOccurred.send(.internalFailure)
                        }
                    }
                    
                    // MARK: - fetching top fitness progresses from server
                    guard let urlTopFitnessProgresses = URL(string: "http://localhost:2305/all") else {
                        self.errorOccurred.send(.incorrectURL)
                        return
                    }
                    
                    let (data3, _) = try await URLSession.shared.data(from: urlTopFitnessProgresses)
                    do {
                        let fitnessProgressDTOs = try JSONDecoder().decode([FitnessProgressDTO.Response].self, from: data3)
                        self.topFitnessProgresses = fitnessProgressDTOs.map { FitnessProgress(fitnessProgress: $0) }
                    } catch {
                        self.errorOccurred.send(.internalFailure)
                    }
                }
                self.isPending = false
            }
        }
    }
    
    func receive() {
        print("---------- Ready for receiving")
        let workItem = DispatchWorkItem { [weak self] in
            self?.webSocket?.receive(completionHandler: { result in
                switch result {
                case .failure(let error):
                    print("Error received: \(error)")
                case .success(let message):
                    switch message {
                    case .string(let string):
                        print("String received: \(string)")
                        DispatchQueue.main.async { [unowned self] in
                            Task {
                                let json = try await JSONSerialization.jsonObject(with: string.data(using: .utf8)!) as! [String: Any]
                                let data = json as [String: Any]
                                self?.errorOccurred.send(.controllerError("Fitness progress \(data["type"]!) on \(data["date"]!) has been added"))
                            }
                        }
                    case .data(let data):
                        print("Data received: \(data)")
                    default:
                        break
                    }
                }
                self?.receive()
            })
        }
        DispatchQueue.global().asyncAfter(deadline: .now() + 1 , execute: workItem)
    }
}

extension Controller: URLSessionWebSocketDelegate {
    func urlSession(_ session: URLSession, webSocketTask: URLSessionWebSocketTask, didOpenWithProtocol protocol: String?) {
        self.receive()
    }
}
