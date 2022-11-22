//
//  DefaultTagsDTOMapper.swift
//  MentalHealth
//
//  Created by alexcampean on 11.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

class DefaultTagsDTOMapper: TagsDTOMapper {
  func makeTagItems(from tagsDTOs: [TagDTOs.Response]) -> TagsDictionary {
    var result = TagsDictionary()
    for tagDTO in tagsDTOs {
      result[tagDTO.id] = makeTagItem(from: tagDTO)
    }
    return result
  }
  
  func makeTagItem(from tagDTO: TagDTOs.Response) -> TagItem {
    TagItem(id: tagDTO.id, text: tagDTO.text)
  }
}
