//
//  DailyGratitudeMockedRepository.swift
//  MentalHealth
//
//  Created by alexcampean on 28.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation
import Combine

class DailyGratitudeMockedRepository: DailyGratitudeRepository {
  private var journalEntries: [DailyGratitudeJournalEntry] = []
  private let timeInterval: TimeInterval
  
  init(timeInterval: TimeInterval) {
    self.timeInterval = timeInterval
    self.addEntries()
  }
  
  /// adds 10 mocked entries in the repository
  private func addEntries() {
    journalEntries = MockedJournalEntriesData().mockedData
  }
  
  func add(journalEntry: DailyGratitudeJournalEntry)
  -> AnyPublisher<DailyGratitudeJournalEntry, RepositoryError> {
    return Future<DailyGratitudeJournalEntry, RepositoryError> { promise in
      DispatchQueue.main.asyncAfter(deadline: .now() + self.timeInterval , execute: {
        self.journalEntries.append(journalEntry)
        promise(.success(journalEntry))
      })
    }.eraseToAnyPublisher()
  }
  
  func delete(journalEntry: DailyGratitudeJournalEntry)
  -> AnyPublisher<DailyGratitudeJournalEntry, RepositoryError> {
    return Future<DailyGratitudeJournalEntry, RepositoryError> { promise in
      DispatchQueue.main.asyncAfter(deadline: .now() + self.timeInterval , execute: {
        guard let index = self.journalEntries.firstIndex(of: journalEntry) else {
          promise(.failure(.entryNotFound))
          return
        }
        self.journalEntries.remove(at: index)
        promise(.success(journalEntry))
      })
    }.eraseToAnyPublisher()
  }
  
  func update(journalEntry: DailyGratitudeJournalEntry)
  -> AnyPublisher<DailyGratitudeJournalEntry, RepositoryError> {
    return Future<DailyGratitudeJournalEntry, RepositoryError> { promise in
      DispatchQueue.main.asyncAfter(deadline: .now() + self.timeInterval , execute: {
        guard let index = self.journalEntries.firstIndex(of: journalEntry) else {
          promise(.failure(.entryNotFound))
          return
        }
        self.journalEntries[index] = journalEntry
        promise(.success(journalEntry))
      })
    }.eraseToAnyPublisher()
  }
  
  func getAllJournalEntriesPublisher()
  -> AnyPublisher<[DailyGratitudeJournalEntry], RepositoryError> {
    return Future<[DailyGratitudeJournalEntry], RepositoryError> { promise in
      DispatchQueue.main.asyncAfter(deadline: .now() + self.timeInterval , execute: {
        promise(.success(self.journalEntries))
      })
    }.eraseToAnyPublisher()
  }
}
