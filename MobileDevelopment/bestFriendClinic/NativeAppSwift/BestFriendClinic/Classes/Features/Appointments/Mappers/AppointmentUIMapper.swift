//
//  AppointmentUIMapper.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/13/22.
//

import Foundation

protocol AppointmentUIMapper {
  func convertToUIModel(from appointment: Appointment) -> AppointmentUIModel
}
