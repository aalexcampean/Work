//
//  DateFormatterExtension.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 12.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

extension DateFormatter {
  static let dateTimeDTOFormatter: DateFormatter = {
    let formatter = DateFormatter()
    formatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ss'Z"
    return formatter
  }()
  
  static let dateTimeFormatter: DateFormatter = {
    let formatter = DateFormatter()
    formatter.dateFormat = "MMMM dd, h:mm a"
    return formatter
  }()
  
  static let dayDateTimeFormatter: DateFormatter = {
    let formatter = DateFormatter()
    formatter.dateFormat = "E, MMMM dd, h:mm a"
    return formatter
  }()
}
