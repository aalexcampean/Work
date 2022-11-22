//
//  IconsCatalog.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/8/22.
//

import SwiftUI

enum AppointmentType: String, CaseIterable {
    case empty = ""
    case earsCleaning = "Ears Cleaning"
    case fleeWash = "Flee Wash"
    case totalWash = "Total Wash"
    case haircut = "Haircut"
    case nailClipping = "Nail Clipping"
    case routineCheckup = "Routine Checkup"
    case teethCleaning = "Teeth Cleaning"
    
    var associatedImage: String {
      switch self {
      case .empty:
          return ""
      case .earsCleaning:
          return "EarsCleaning"
      case .fleeWash:
          return "FleeWash"
      case .totalWash:
          return "TotalWash"
      case .haircut:
          return "Haircut"
      case .nailClipping:
          return "NailClipping"
      case .routineCheckup:
          return "RoutineCheckup"
      case .teethCleaning:
          return "TeethCleaning"
      }
    }
    
    var associatedPrice: Int {
      switch self {
      case .empty:
          return 0
      case .earsCleaning:
          return 90
      case .fleeWash:
          return 200
      case .totalWash:
          return 150
      case .haircut:
          return 100
      case .nailClipping:
          return 70
      case .routineCheckup:
          return 50
      case .teethCleaning:
          return 70
      }
    }
}
