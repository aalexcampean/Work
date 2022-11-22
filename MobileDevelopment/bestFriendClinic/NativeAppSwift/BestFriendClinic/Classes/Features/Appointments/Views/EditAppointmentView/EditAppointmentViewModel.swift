//
//  EditAppointmentViewModel.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/21/22.
//

import Foundation

class EditAppointmentViewModel: ObservableObject {
    // MARK: - Dependencies
    private var service: AppointmentsService
    private var state: AppointmetsState
    private var appointment: AppointmentUIModel?
    
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
    init(service: AppointmentsService, state: AppointmetsState, appointment: AppointmentUIModel?) {
        self.service = service
        self.state = state
        self.appointment = appointment
        
        setFields()
    }
    
    func setFields() {
        guard let validAppointment = appointment else {
            return
        }
        
        let formattedDate = DateFormatter.dateTimeFormatter.date(from: validAppointment.date)!
        
        typeSelection = validAppointment.type
        dateSelection = formattedDate
        locationSelection = validAppointment.location
        vetSelection = validAppointment.vetName
        petSelection = validAppointment.petName
        inputDescription = validAppointment.description ?? ""
    }
    
    func selectTextField() {
        isTextFieldSelected.toggle()
    }
    
    func updateAppointment() {
        guard inputIsValid() else {
            return
        }
        service.update(appointment: createAppointment())
    }
    
    func inputIsValid() -> Bool {
        return typeSelection != .empty && !locationSelection.isEmpty && !petSelection.isEmpty && !vetSelection.isEmpty
    }
    
    private func createAppointment() -> Appointment {
        guard let validAppointment = appointment else {
            return Appointment(id: UUID().uuidString,
                               type: typeSelection.rawValue,
                               date: dateSelection,
                               location: locationSelection,
                               petName: petSelection,
                               vetName: vetSelection,
                               description: inputDescription)
        }
        
        return Appointment(id: validAppointment.id,
                           type: typeSelection.rawValue,
                           date: dateSelection,
                           location: locationSelection,
                           petName: petSelection,
                           vetName: vetSelection,
                           description: inputDescription)
    }
}
