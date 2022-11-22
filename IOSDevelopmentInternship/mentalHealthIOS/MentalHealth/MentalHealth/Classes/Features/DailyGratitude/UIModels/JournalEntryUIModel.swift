//
//  JournalEntry.swift
//  MentalHealth
//
//  Created by alexcampean on 23.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

struct JournalEntryUIModel: Identifiable {
  let id: String
  var title: String
  var image: ImageSource
  var publicationDate: String
  var tags: [TagUIModel]
  var associatedImages: [ImageSource]
}
