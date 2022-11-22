//
//  DefaultAppointmentUIMapper.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/13/22.
//

import Foundation

class DefaultAppointmentUIMapper: AppointmentUIMapper {
    func convertToUIModel(from appointment: Appointment) -> AppointmentUIModel {
        let type = AppointmentType(rawValue: appointment.type)!
        
        let date = DateFormatter.dateTimeFormatter.string(from: appointment.date)
        
        return  AppointmentUIModel(id: appointment.id,
                                   type: type,
                                   date: date,
                                   location: appointment.location,
                                   petName: appointment.petName,
                                   vetName: appointment.vetName,
                                   description: appointment.description)
    }
}
