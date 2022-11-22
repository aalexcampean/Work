//
//  AppointmentSectionUIModel.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/10/22.
//

import Foundation

struct AppointmentSectionUIModel: Identifiable, Equatable {
    static func == (lhs: AppointmentSectionUIModel, rhs: AppointmentSectionUIModel) -> Bool {
        return lhs.id == rhs.id
    }
    
    let id = UUID()
    var title: String
    var items: [AppointmentUIModel]
}
