//
//  AppointmentDetailsViewModel.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/15/22.
//

import Foundation
import SwiftUI

// MARK: - Type Alias for the a new type of LoadingState
typealias EntryUIState = LoadingState<AppointmentUIModel, AppointmentPresentationError>

class AppointmentDetailsViewModel: ObservableObject {
    // MARK: - Dependencies
    private var service: AppointmentsService
    private var state: AppointmetsState
    private var mapper: AppointmentUIMapper
    private let appointmentID: String
    
    // MARK: - Published Properties
    @Published private(set) var presentationState: EntryUIState = .loading()
    @Published var isDeleteAppointmentAlertShown: Bool = false
    @Published var isUpdateAppointmentViewShown: Bool = false
    
    // MARK: - Published properties
    @Published var typeSelection: AppointmentType = .earsCleaning
    @Published var dateSelection: Date = Date.now
    @Published var locationSelection: String = "Str. Paris nr. 20"
    @Published var petSelection: String = "Abel"
    @Published var vetSelection: String = "Irina Pop"
    @Published var inputDescription : String = ""
    @Published var isTextFieldSelected: Bool = false
    
    // MARK: - Constants
    let updateAppointmentTitle = "Edit appointment"
    let typeOptions: [AppointmentType] = [.earsCleaning, .fleeWash, .haircut, .nailClipping, .routineCheckup, .teethCleaning, .totalWash]
    let locationOptions: [String] = ["Str. Paris nr. 20", "Str. Republicii nr. 30"]
    let petOptions: [String] = ["Abel", "Ludmila", "Snowflake"]
    let vetOptions: [String] = ["Irina Pop", "Claudiu Marinescu", "Mihai Ipate", "Rebeca Campean"]
    
    // MARK: - Init
    init(service: AppointmentsService, state: AppointmetsState, mapper: AppointmentUIMapper, appointmentID: String) {
        self.service = service
        self.state = state
        self.mapper = mapper
        self.appointmentID = appointmentID
        
        // MARK: Setup
        attachToState()
        
        setFields()
    }
    
    // MARK: - Attach to state
    private func attachToState() {
        state.$appointmentsState.receive(on: RunLoop.main)
            .map(makeUIState)
            .assign(to: &$presentationState)
    }
    
    private func makeUIState(from state: EntriesState) -> EntryUIState {
        switch state {
        case .loading(currentValue: let currentAppointments):
            return .loading(currentValue: self.selectAppointment(from: currentAppointments))
            
        case .loaded(let allAppointments):
            let appointmentUIModel = self.selectAppointment(from: allAppointments)
            
            if let validAppointment = appointmentUIModel {
                let formattedDate = DateFormatter.dateTimeFormatter.date(from: validAppointment.date)!
                
                typeSelection = validAppointment.type
                dateSelection = formattedDate
                locationSelection = validAppointment.location
                vetSelection = validAppointment.vetName
                petSelection = validAppointment.petName
                inputDescription = validAppointment.description ?? ""
            }
            
            return .loaded(newValue: appointmentUIModel)
            
        case .failed(let error, let currentAppointments):
            return .failed(.failure(error.toString()), currentValue: self.selectAppointment(from: currentAppointments))
        }
    }
    
    private func selectAppointment(from appointments: [Appointment]?) -> AppointmentUIModel? {
        guard let appointments = appointments else {
            return nil
        }
        
        guard let appointment = appointments.first(where: { $0.id == self.appointmentID }) else {
          return nil
        }
        
        return mapper.convertToUIModel(from: appointment)
    }
    
    func setFields() {
        guard let validAppointment = presentationState.currentValue else {
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
    
    func showUpdateAppointmentView() {
        isUpdateAppointmentViewShown.toggle()
    }
    
    func showDeleteAppointmentAlert() {
        isDeleteAppointmentAlertShown.toggle()
    }
    
    func deleteAppointment() {
        guard let appointmentModel = presentationState.currentValue else {
            return
        }
        
        service.delete(appointment: Appointment(id: appointmentModel.id,
                                                type: appointmentModel.type.rawValue,
                                                date: Date.now,
                                                location: appointmentModel.location,
                                                petName: appointmentModel.petName,
                                                vetName: appointmentModel.vetName,
                                                description: appointmentModel.description))
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
        guard let validAppointment = presentationState.currentValue else {
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
