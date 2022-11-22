//
//  Appointment.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/13/22.
//

import Foundation

struct Appointment: Identifiable, Equatable, Comparable {
    let id: String
    let type: String
    let date: Date
    let location: String
    var petName: String
    var vetName: String
    let description: String?
    
    static func == (lhs: Appointment, rhs: Appointment) -> Bool {
        return lhs.id == rhs.id
    }
    
    static func < (lhs: Appointment, rhs: Appointment) -> Bool {
        return lhs.date < rhs.date
    }
}
