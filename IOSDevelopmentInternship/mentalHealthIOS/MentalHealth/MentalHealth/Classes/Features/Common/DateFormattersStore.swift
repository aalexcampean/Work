//
//  DateFormattersStore.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 14.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

enum DateFormattersStore {
  static let dtoDateFormatter: DateFormatter = .dateTimeDTOFormatter
  static let uiDateFormatter: DateFormatter = .dateTimeFormatter
  static let uiExtendedDateFormatter: DateFormatter = .dayDateTimeFormatter
}
