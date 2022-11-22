//
//  DefaultAppointmentsService.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/14/22.
//

import Foundation
import Combine

class DefaultAppointmentsService: AppointmentsService {
    // MARK: - Dependencies
    private var repository: AppointmentsRepository
    
    // MARK: - Private Properties
    private var state: AppointmetsState
    private lazy var subscriptions: [AnyCancellable] = []
    
    // MARK: - Init
    init(repository: AppointmentsRepository, state: AppointmetsState) {
        self.repository = repository
        self.state = state
    }
    
    func add(appointment: Appointment) {
        beginLoading()
        
        let addPublisher = self.repository.add(appointment: appointment)
        
        addPublisher.sink { completion in
            switch completion {
            case .finished:
                debugPrint("Appointment added successfully")
                
            case .failure(let addError):
                debugPrint("Add Operation failed: \(addError)")
                self.endLoading(error: addError)
            }
        } receiveValue: { appointment in
            var appointments = self.state.appointmentsState.currentValue
            
            appointments?.append(appointment)
            self.endLoading(appointments: appointments)
        }.store(in: &subscriptions)
    }
    
    func update(appointment: Appointment) {
        beginLoading()
        
        debugPrint(appointment)
        
        let updatePublisher = self.repository.update(updatedAppointment: appointment)
        
        updatePublisher.sink { completion in
            switch completion {
            case .finished:
                debugPrint("Appointment updated successfully")
                
            case .failure(let updateError):
                debugPrint("Update Operation failed: \(updateError)")
                self.endLoading(error: updateError)
            }
        } receiveValue: { appointment in
            var appointments = self.state.appointmentsState.currentValue
            guard let index = appointments?.firstIndex(of: appointment) else {
                self.endLoading(error: .entryNotFound)
                return
            }
            
            appointments?[index] = appointment
            self.endLoading(appointments: appointments)
        }.store(in: &subscriptions)
    }
    
    func delete(appointment: Appointment) {
        beginLoading()
        
        let deletePublisher = self.repository.delete(appointment: appointment)
        
        deletePublisher.sink { completion in
            switch completion {
            case .finished:
                debugPrint("Appointments deleted successfully")
                
            case .failure(let deleteError):
                debugPrint("Delete Operation failed")
                self.endLoading(error: deleteError)
            }
        } receiveValue: { appointment in
            var appointments = self.state.appointmentsState.currentValue
            guard let index = appointments?.firstIndex(of: appointment) else {
                self.endLoading(error: .entryNotFound)
                return
            }
            
            appointments?.remove(at: index)
            self.endLoading(appointments: appointments)
        }.store(in: &subscriptions)
    }
    
    func fetchAll() {
        beginLoading()
        
        let appointmentsPublisher = self.repository.getAll()
        
        appointmentsPublisher
            .eraseToAnyPublisher()
            .sink { completion in
                switch completion {
                case .finished:
                    debugPrint("Appointments fetched successfully")
                    
                case .failure(let fetchError):
                    debugPrint("Fetch Operation failed: \(fetchError)")
                    self.endLoading(error: fetchError)
                }
            } receiveValue: { appointments in
                self.endLoading(appointments: appointments)
            }
            .store(in: &subscriptions)
    }
    
    private func beginLoading() {
        state.appointmentsState = .loading(currentValue: state.appointmentsState.currentValue)
    }
    
    private func endLoading(appointments: [Appointment]?) {
        state.appointmentsState = .loaded(newValue: appointments)
    }
    
    private func endLoading(error: RepositoryError) {
        state.appointmentsState = .failed(error, currentValue: state.appointmentsState.currentValue)
    }
    
}
