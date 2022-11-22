//
//  DailyGratitudeDTOs.swift
//  MentalHealth
//
//  Created by alexcampean on 05.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation
import SwiftUI

enum DailyGratitudeDTOs {
  struct Request: Encodable {
    let title: String?
    let image: String?
    let publicationDate: String
    let tags: [String]
    
    enum CodingKeys: String, CodingKey {
      case title = "text"
      case image = "picture"
      case publicationDate = "time"
      case tags
    }
  }
  
  struct Response: Codable {
    let identifier: Int
    let publicationDate: String
    let title: String?
    let image: String?
    let tags: [String]
    
    enum CodingKeys: String, CodingKey {
      case identifier = "id"
      case publicationDate = "time"
      case title = "text"
      case image = "picture"
      case tags
    }
  }
}
