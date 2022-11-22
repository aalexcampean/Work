//
//  DateExtension.swift
//  MentalHealth
//
//  Created by alexcampean on 01.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

extension Date {
  /// Defines the constants representing the no. seconds in the specified time interval
  struct Interval {
    static let sevenDays = 604800
    static let oneMonth = 2678400
    static let oneYear = 31536000
  }
  
  /// Defines 3 time intervals in the last year
  enum PastTimeInterval {
    case pastSevenDays
    case pastMonth
    case pastYear
    
    /// Returns the afferent time interval
    func returnRandomInterval() -> TimeInterval {
      switch self {
      case .pastSevenDays:
        return TimeInterval(.random(in: -Interval.sevenDays ... 0))
        
      case .pastMonth:
        return TimeInterval(.random(in: -Interval.oneMonth ... -Interval.sevenDays))
        
      case .pastYear:
        return TimeInterval(.random(in: -Interval.oneYear ... -Interval.oneMonth))
      }
    }
  }
  
  /// Generates a random past date in the last year
  func subtractedRandomly() -> Date {
    let radomTimeIterval = [PastTimeInterval.pastSevenDays, .pastMonth, .pastYear].randomElement()!
    return self.advanced(by: radomTimeIterval.returnRandomInterval())
  }
}
