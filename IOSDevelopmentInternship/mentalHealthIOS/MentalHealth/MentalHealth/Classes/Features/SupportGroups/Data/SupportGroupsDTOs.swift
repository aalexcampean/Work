//
//  SupportGroupsDTOs.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 05.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

enum SupportGroupsDTOs {
  struct EventResponse: Decodable {
    let id: String
    let title: String
    let image: String?
    let location: String
    let address: String
    let description: String
    let startDateAndTime: String
    let tags: [String]
    let isBookmarked: Bool
    let isJoined: Bool
    
    enum CodingKeys: String, CodingKey {
      case id
      case title = "name"
      case image
      case location
      case address
      case description
      case startDateAndTime = "dateTime"
      case tags
      case isBookmarked
      case isJoined
    }
  }
  
  struct EventRequest: Encodable {
    let id: String
    let title: String
    let image: String
    let location: String
    let address: String
    let description: String
    let startDateAndTime: String
    let tags: [String]
    let isBookmarked: Bool
    let isJoined: Bool
    
    enum CodingKeys: String, CodingKey {
      case id
      case title = "name"
      case image
      case location
      case address
      case description
      case startDateAndTime = "dateTime"
      case tags
      case isBookmarked
      case isJoined
    }
  }
}
