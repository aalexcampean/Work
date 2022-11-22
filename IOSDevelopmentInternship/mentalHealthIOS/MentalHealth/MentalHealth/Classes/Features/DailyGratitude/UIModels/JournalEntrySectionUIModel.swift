//
//  JournalEntrySectionModel.swift
//  MentalHealth
//
//  Created by alexcampean on 24.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

struct JournalEntrySectionUIModel: Identifiable {
  let id = UUID()
  var title: String
  var items: [JournalEntryUIModel]
}
