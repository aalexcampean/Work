//
//  AppointmentUIModel.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/9/22.
//

import Foundation
import SwiftUI

struct AppointmentUIModel: Identifiable, Equatable, Comparable {
    let id: String
    var type: AppointmentType
    var date: String
    var location: String
    var petName: String
    var vetName: String
    var description: String?
    
    static func == (lhs: AppointmentUIModel, rhs: AppointmentUIModel) -> Bool {
      return lhs.id == rhs.id
    }
    
    static func < (lhs: AppointmentUIModel, rhs: AppointmentUIModel) -> Bool {
      return lhs.date < rhs.date
    }
}
