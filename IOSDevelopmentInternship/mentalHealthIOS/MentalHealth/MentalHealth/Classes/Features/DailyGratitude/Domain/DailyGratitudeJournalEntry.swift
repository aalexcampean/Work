//
//  DailyGratitudeJournalEntry.swift
//  MentalHealth
//
//  Created by alexcampean on 24.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

struct DailyGratitudeJournalEntry: Equatable, Comparable {
  let identifier: String
  let title: String
  let image: String?
  let publicationDate: Date
  let tags: [String]
  
  var associatedTags: [TagItem]? = nil
  
  static func == (lhs: DailyGratitudeJournalEntry, rhs: DailyGratitudeJournalEntry) -> Bool {
    return lhs.identifier == rhs.identifier
  }
  
  static func < (lhs: DailyGratitudeJournalEntry, rhs: DailyGratitudeJournalEntry) -> Bool {
    return lhs.publicationDate < rhs.publicationDate
  }
}
