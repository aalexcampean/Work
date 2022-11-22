//
//  AddAppointmentViewModel.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/13/22.
//

import Foundation

class AddAppointmentViewModel: ObservableObject {
    // MARK: - Dependencies
    private var service: AppointmentsService
    private var state: AppointmetsState
    
    // MARK: - Published properties
    @Published var typeSelection: AppointmentType = .earsCleaning
    @Published var dateSelection: Date = Date.now
    @Published var locationSelection: String = "Str. Paris nr. 20"
    @Published var petSelection: String = "Abel"
    @Published var vetSelection: String = "Irina Pop"
    @Published var inputDescription : String = ""
    @Published var isTextFieldSelected: Bool = false
    
    // MARK: - Constants
    let addAppointmentTitle = "New appointment"
    let typeOptions: [AppointmentType] = [.earsCleaning, .fleeWash, .haircut, .nailClipping, .routineCheckup, .teethCleaning, .totalWash]
    let locationOptions: [String] = ["Str. Paris nr. 20", "Str. Republicii nr. 30"]
    let petOptions: [String] = ["Abel", "Ludmila", "Snowflake"]
    let vetOptions: [String] = ["Irina Pop", "Claudiu Marinescu", "Mihai Ipate", "Rebeca Campean"]
    
    // MARK: - Init
    init(service: AppointmentsService, state: AppointmetsState) {
        self.service = service
        self.state = state
    }
    
    func selectTextField() {
        isTextFieldSelected.toggle()
    }
    
    func addAppointment() {
        guard inputIsValid() else {
            return
        }
        service.add(appointment: createAppointment())
    }
    
    func inputIsValid() -> Bool {
        return typeSelection != .empty && !locationSelection.isEmpty && !petSelection.isEmpty && !vetSelection.isEmpty
    }
    
    private func createAppointment() -> Appointment {
        return Appointment(id: UUID().uuidString,
                           type: typeSelection.rawValue,
                           date: dateSelection,
                           location: locationSelection,
                           petName: petSelection,
                           vetName: vetSelection,
                           description: inputDescription)
    }
}
