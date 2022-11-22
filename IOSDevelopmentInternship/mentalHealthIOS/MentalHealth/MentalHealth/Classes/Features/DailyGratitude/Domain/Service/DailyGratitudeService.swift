//
//  DailyGratitudeService.swift
//  MentalHealth
//
//  Created by alexcampean on 29.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

protocol DailyGratitudeService {
  func addJournalEntry(journalEntry: DailyGratitudeJournalEntry)
  func updateJournalEntry(journalEntry: DailyGratitudeJournalEntry)
  func deleteJournalEntry(journalEntry: DailyGratitudeJournalEntry)
  func fetchAllJournalEntries()
}
