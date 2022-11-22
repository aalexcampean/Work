//
//  TagsDTOMapper.swift
//  MentalHealth
//
//  Created by alexcampean on 11.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

protocol TagsDTOMapper {
  func makeTagItems(from tagsDTOs: [TagDTOs.Response]) -> TagsDictionary
  func makeTagItem(from tagDTO: TagDTOs.Response) -> TagItem
}
