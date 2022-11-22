//
//  TagItem.swift
//  MentalHealth
//
//  Created by alexcampean on 07.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

typealias TagID = String

struct TagItem: Equatable, Comparable {
  let id: String
  let text: String
  
  static func == (lhs: TagItem, rhs: TagItem) -> Bool {
    return lhs.id == rhs.id
  }
  
  static func < (lhs: TagItem, rhs: TagItem) -> Bool {
    return lhs.text < rhs.text
  }
}
