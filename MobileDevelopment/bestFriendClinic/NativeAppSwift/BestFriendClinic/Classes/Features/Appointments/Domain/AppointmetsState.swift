//
//  AppointmetsState.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/14/22.
//

import Foundation

class AppointmetsState: ObservableObject {
    @Published var appointmentsState: LoadingState<[Appointment], RepositoryError> = .loading()
}
