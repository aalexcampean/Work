//
//  DailyGratitudeRepository.swift
//  MentalHealth
//
//  Created by alexcampean on 29.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation
import Combine

typealias JournalEntryPublisher = AnyPublisher<DailyGratitudeJournalEntry, RepositoryError>
typealias JournalEntriesPublisher = AnyPublisher<[DailyGratitudeJournalEntry], RepositoryError>

protocol DailyGratitudeRepository {
  func add(journalEntry: DailyGratitudeJournalEntry) -> JournalEntryPublisher
  func delete(journalEntry: DailyGratitudeJournalEntry) -> JournalEntryPublisher
  func update(journalEntry: DailyGratitudeJournalEntry) -> JournalEntryPublisher
  
  func getAllJournalEntriesPublisher() -> JournalEntriesPublisher
}
