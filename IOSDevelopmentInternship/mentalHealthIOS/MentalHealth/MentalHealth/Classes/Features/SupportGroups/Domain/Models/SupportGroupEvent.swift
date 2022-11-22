//
//  SupportGroupEvent.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 25.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

struct SupportGroupEvent: Equatable, Comparable {
  enum Location {
    case online(name: String, link: URL?)
    case onsite(name: String, location: String)
  }
  
  let identifier: String
  let title: String
  let image: String?
  let startDateAndTime: Date
  let location: Location
  let description: String
  let tags: [String]
  var associatedTags: [TagItem] = []
  var isBookmarked: Bool
  var isJoined: Bool
  
  static func == (lhs: SupportGroupEvent, rhs: SupportGroupEvent) -> Bool {
    return lhs.identifier == rhs.identifier
  }
  
  static func < (lhs: SupportGroupEvent, rhs: SupportGroupEvent) -> Bool {
    return lhs.startDateAndTime < rhs.startDateAndTime
  }
}
