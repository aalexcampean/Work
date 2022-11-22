//
//  ImageSource.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 23.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

enum ImageSource: Hashable {
  case url(URL)
  case asset(String)
  case system(String)
  case placeholder
}
