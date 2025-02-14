//
//  CalendarExtension.swift
//  MentalHealth
//
//  Created by alexcampean on 01.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

extension Calendar {
  /// Checks if a given date is this week
  func isDateThisWeek(_ date: Date) -> Bool {
    return self.isDate(Date(), equalTo: date, toGranularity: .weekOfYear)
  }
  /// Checks if a given date is this month
  func isDateThisMonth(_ date: Date) -> Bool {
    return self.isDate(Date(), equalTo: date, toGranularity: .month)
  }
  
  /// Checks if a given date is in the future
  func isDateInFuture(_ date: Date) -> Bool {
    guard let days = self.dateComponents([.day], from: Date.now, to: date).day else {
      return false
    }
    return days >= 0
  }
}
