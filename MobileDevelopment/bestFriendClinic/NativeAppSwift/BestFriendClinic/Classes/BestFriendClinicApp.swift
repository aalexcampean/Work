//
//  BestFriendClinicApp.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/7/22.
//

import SwiftUI

class AppointmentsFeatureDependencies: ObservableObject {
    private(set) var state: AppointmetsState
    private(set) var service: AppointmentsService
    private(set) var mapper: AppointmentUIMapper
    
    init(state: AppointmetsState, service: AppointmentsService, mapper: AppointmentUIMapper) {
        self.state = state
        self.service = service
        self.mapper = mapper
    }
}

@main
struct BestFriendClinicApp: App {
    private var appointmentsDependencies: AppointmentsFeatureDependencies = {
      let state = AppointmetsState()
      let mockedRepository = MockedAppointmentsRepository(timeInterval: 0.3)
      let appointmentsMapper = DefaultAppointmentUIMapper()
      let service = DefaultAppointmentsService(repository: mockedRepository, state: state)
      return AppointmentsFeatureDependencies(state: state, service: service, mapper: appointmentsMapper)
    }()
    
    var body: some Scene {
        WindowGroup {
            MainLandingView()
                .environmentObject(appointmentsDependencies)
        }
    }
}
