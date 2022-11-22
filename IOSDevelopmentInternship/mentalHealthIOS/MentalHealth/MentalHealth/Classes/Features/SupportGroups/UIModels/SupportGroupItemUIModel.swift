//
//  SupportGroupItemUIModel.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 22.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation
import OrderedCollections

struct SupportGroupItemUIModel: Identifiable {
  
  enum Attribute: Hashable {
    case isBookmarked(String)
    case isJoined(String)
  }
  
  var hasAttributes: Bool {
    return !attributes.isEmpty
  }
  
  var hasTags: Bool {
    return !tags.isEmpty
  }
  
  var hasParticipants: Bool {
    return !participants.isEmpty
  }
  
  let id: String
  let title: String
  let image: ImageSource
  let startDate: String
  let startDateExtended: String
  let location: String
  var link: URL?
  let description: String
  let tags: [TagUIModel]
  var attributes: OrderedSet<Attribute>
  var joinActionTitle: String
  var participants: [ImageSource]
  var calendarUrl: String
}
