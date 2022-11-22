//
//  AppointmentCardViewModel.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/13/22.
//

import Foundation
import SwiftUI

class AppointmentCardViewModel: ObservableObject {
    // MARK: - Dependencies
    var appointment: AppointmentUIModel
    private var service: AppointmentsService
    private var state: AppointmetsState
    
    @State var deleteAlertIsShown: Bool = false
    
    // MARK: - Init
    init(appointment: AppointmentUIModel, service: AppointmentsService, state: AppointmetsState) {
        self.appointment = appointment
        self.service = service
        self.state = state
    }
        
    func deleteAppointment() {
        let appointmentModel = Appointment(id: appointment.id,
                                      type: appointment.type.rawValue,
                                      date: Date.now,
                                      location: appointment.location,
                                      petName: appointment.petName,
                                      vetName: appointment.vetName,
                                      description: appointment.description)
        
        deleteAlertIsShown.toggle()
        service.delete(appointment: appointmentModel)
    }
}
