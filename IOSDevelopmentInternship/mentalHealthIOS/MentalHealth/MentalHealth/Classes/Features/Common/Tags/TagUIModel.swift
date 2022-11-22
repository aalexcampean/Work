//
//  TagUIModel.swift
//  MentalHealth
//
//  Created by alexcampean on 20.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

struct TagUIModel: Hashable {
  let id: String
  let text: String
  var isSelected: Bool = false
}
