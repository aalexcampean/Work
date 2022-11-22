//
//  DefaultJournalEntryDTOMapper.swift
//  MentalHealth
//
//  Created by alexcampean on 11.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

class DefaultJournalEntryDTOMapper: JournalEntryDTOMapper {
  private lazy var dateFormatter: DateFormatter = {
    let formatter = DateFormatter()
    formatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ss.SSS"
    return formatter
  }()
  
  func makeJournalEntries(from journalEntriesDTO: [DailyGratitudeDTOs.Response]) -> [DailyGratitudeJournalEntry] {
    var result: [DailyGratitudeJournalEntry] = []
    for entryDTO in journalEntriesDTO {
      result.append(makeJournalEntry(from: entryDTO))
    }
    return result
  }
  
  func makeJournalEntry(from journalEntryDTO: DailyGratitudeDTOs.Response) -> DailyGratitudeJournalEntry {
    var date = Date.now
    
    if let validDate = dateFormatter.date(from: journalEntryDTO.publicationDate) {
      date = validDate
    }
    
    /// Checking if the Image is nil
    var imageURL: String? = nil
    if let validImage = journalEntryDTO.image {
      imageURL = validImage
    }
    /// Checking if the Title is nil
    var title: String = ""
    if let validTitle = journalEntryDTO.title {
      title = validTitle
    }
    
    let journalEntry = DailyGratitudeJournalEntry(identifier: String(journalEntryDTO.identifier),
                                                  title: title,
                                                  image: "https://images.unsplash.com/photo-1515338580809-319aaaae76fd?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=2370&q=80",
                                                  publicationDate: date,
                                                  tags: journalEntryDTO.tags)
    return journalEntry
  }
}
