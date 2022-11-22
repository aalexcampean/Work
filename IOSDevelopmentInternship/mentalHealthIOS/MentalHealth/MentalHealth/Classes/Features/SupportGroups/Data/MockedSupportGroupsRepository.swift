//
//  MockedSupportGroupsRepository.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 29.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation
import Combine

class MockedSupportGroupsRepository: SupportGroupsRepository {
  
  // MARK: - Private Properties
  
  private var events: [SupportGroupEvent] = []
  private var timeInterval: TimeInterval
  private var failAllOperations: Bool
  private let mapper: SupportGroupsDTOMapper
  
  // MARK: - Init
  
  init(timeInterval: TimeInterval,
       failAllOperations: Bool = false,
       mapper: SupportGroupsDTOMapper) {
    self.timeInterval = timeInterval
    self.failAllOperations = failAllOperations
    self.mapper = mapper
  }
  
  // MARK: - SupportGroupsRepository
  
  func add(event: SupportGroupEvent) -> AnyPublisher<SupportGroupEvent, RepositoryError> {
    return Future<SupportGroupEvent, RepositoryError> { promise in
      DispatchQueue.global(qos: .background).async {
        do {
          self.events.append(event)
          try self.writeToFile()
          DispatchQueue.main.async {
            promise(.success(event))
          }
        } catch {
          DispatchQueue.main.async {
            promise(.failure(.internalFailure))
          }
        }
      }
    }
    .eraseToAnyPublisher()
  }
  
  func update(updatedEvent: SupportGroupEvent) -> AnyPublisher<SupportGroupEvent, RepositoryError> {
    return Future<SupportGroupEvent, RepositoryError> { promise in
      DispatchQueue.main.asyncAfter(deadline: .now() + self.timeInterval, execute: {
        do {
          guard !self.failAllOperations else {
            promise(.failure(.internalFailure))
            return
          }
          
          guard let index = self.events.firstIndex(where: {event in
            return event == updatedEvent
          }) else {
            promise(.failure(.entryNotFound))
            return
          }
          
          self.events[index] = updatedEvent
          try self.writeToFile()
          promise(.success(updatedEvent))
        } catch {
          promise(.failure(.internalFailure))
        }
      })
    }
    .eraseToAnyPublisher()
  }
  
  func delete(event: SupportGroupEvent) -> AnyPublisher<SupportGroupEvent, RepositoryError> {
    return Future<SupportGroupEvent, RepositoryError> { promise in
      DispatchQueue.main.asyncAfter(deadline: .now() + self.timeInterval, execute: {
        do {
          guard !self.failAllOperations else {
            promise(.failure(.internalFailure))
            return
          }
          
          guard let index = self.events.firstIndex(where: { (existingItem) -> Bool in
            return existingItem == event
          }) else {
            promise(.failure(.entryNotFound))
            return
          }
          
          self.events.remove(at: index)
          try self.writeToFile()
          promise(.success(event))
        } catch {
          promise(.failure(.internalFailure))
        }
      })
    }
    .eraseToAnyPublisher()
  }
  
  func getAllEventsPublisher() -> AnyPublisher<[SupportGroupEvent], RepositoryError> {
    return Future<[SupportGroupEvent], RepositoryError> { promise in
      DispatchQueue.global(qos: .background).async {
        do {
          let events = try self.readFromFile()
          DispatchQueue.main.async {
            promise(.success(events))
          }
          self.events = events
        } catch {
          debugPrint(error)
          DispatchQueue.main.async {
            promise(.failure(RepositoryError.internalFailure))
          }
        }
      }
    }
    .eraseToAnyPublisher()
  }
  
  private func fileURL() throws -> URL {
    try FileManager.default.url(for: .documentDirectory,
                                   in: .userDomainMask,
                                   appropriateFor: nil,
                                   create: false)
      .appendingPathComponent("events.data")
  }
  
  private func writeToFile() throws {
    let eventDTOs = self.events.map(self.mapper.convertToDTO)
    let data = try JSONEncoder().encode(eventDTOs)
    let outfile = try self.fileURL()
    try data.write(to: outfile)
  }
  
  private func readFromFile() throws -> [SupportGroupEvent] {
    let fileURL = try self.fileURL()
    let file = try FileHandle(forReadingFrom: fileURL)
    let eventDTOs = try JSONDecoder().decode([SupportGroupsDTOs.EventResponse].self,
                                             from: file.availableData)
    let events = DefaultSupportGroupsDTOMapper().convertToEventsArray(from: eventDTOs)
    return events
  }
}

extension Date {
  func randomFutureDate() -> Date {
    /// 0-60 days in the future
    let interval = TimeInterval.random(in: 0...5184000)
    return self.advanced(by: interval)
  }
}
