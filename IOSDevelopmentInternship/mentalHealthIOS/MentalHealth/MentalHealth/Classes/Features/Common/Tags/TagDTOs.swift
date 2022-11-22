//
//  TagDTOs.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 05.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

enum TagDTOs {
  struct Response: Decodable {
    let id: String
    let text: String
    
    enum CodingKeys: String, CodingKey {
      case id
      case text = "name"
    }
  }
  
  struct Request: Encodable {
    let id: String
  }
}
