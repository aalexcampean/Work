//
//  JournalEntryDTOMapper.swift
//  MentalHealth
//
//  Created by alexcampean on 11.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

protocol JournalEntryDTOMapper {
  func makeJournalEntries(from journalEntriesDTO: [DailyGratitudeDTOs.Response]) -> [DailyGratitudeJournalEntry]
  func makeJournalEntry(from journalEntryDTO: DailyGratitudeDTOs.Response) -> DailyGratitudeJournalEntry
}
