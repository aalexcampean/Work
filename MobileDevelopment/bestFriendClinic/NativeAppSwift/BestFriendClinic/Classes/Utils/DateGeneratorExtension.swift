//
//  DateGeneratorExtension.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/14/22.
//

import Foundation

extension Date {
    /// Defines the constants representing the no. seconds in the specified time interval
    struct Interval {
        static let sevenDays = 604800
        static let oneMonth = 2678400
        static let oneYear = 31536000
    }
    
    /// Defines time intervals in the next year and previous one
    enum FutureAndPastTimeInterval {
//        case previous
        case nextSevenDays
        case nextMonth
        case nextYear
        
        /// Returns the afferent time interval
        func returnRandomInterval() -> TimeInterval {
            switch self {
//            case .previous:
//                return TimeInterval(.random(in: -Interval.oneYear ... 0))
                
            case .nextSevenDays:
                return TimeInterval(.random(in: 0 ... Interval.sevenDays))
                
            case .nextMonth:
                return TimeInterval(.random(in: Interval.sevenDays ... Interval.oneMonth))
                
            case .nextYear:
                return TimeInterval(.random(in: Interval.oneMonth ... Interval.oneYear))
            }
        }
    }
    /// Generates a random future or past date in the last year
    func generateRandomly() -> Date {
        let radomTimeIterval = [FutureAndPastTimeInterval.nextSevenDays, .nextMonth, .nextYear].randomElement()!
        return self.advanced(by: radomTimeIterval.returnRandomInterval())
    }
}
