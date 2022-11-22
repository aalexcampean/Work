//
//  AppointmentsService.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/14/22.
//

import Foundation

protocol AppointmentsService {
    func add(appointment: Appointment)
    func update(appointment: Appointment)
    func delete(appointment: Appointment)
    func fetchAll()
}
