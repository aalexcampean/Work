//
//  AppointmentsViewModel.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/13/22.
//

import Foundation
import Combine

// MARK: - Type Alias for the 2 types of LoadingState
typealias EntriesState = LoadingState<[Appointment], RepositoryError>
typealias EntriesUIState = LoadingState<[AppointmentSectionUIModel], AppointmentPresentationError>

class AppointmentsViewModel: ObservableObject {
    // MARK: - Published properties
    @Published private(set) var presentationState: EntriesUIState = .loading()
    
    // MARK: - Dependencies
    private var service: AppointmentsService
    private var state: AppointmetsState
    private var mapper: AppointmentUIMapper
    
    // MARK: - Public Properties
    let listTitle = "Appointments"
    
    // MARK: - Constants
    let title = "Appointments"
    enum Section: Int {
//        case previous
        case thisWeek
        case thisMonth
        case thisYear
        case upcoming
        
        func toString() -> String {
            switch self {
//            case .previous:
//                return "Previous"
            case .thisWeek:
                return "This week"
            case .thisMonth:
                return "This month"
            case .thisYear:
                return "This year"
            case .upcoming:
                return "Upcoming"
            }
        }
    }
    
    // MARK: - Init
    init(service: AppointmentsService, state: AppointmetsState, mapper: AppointmentUIMapper) {
        self.service = service
        self.state = state
        self.mapper = mapper
        
        fetchAppointments()
        
        // MARK: Setup
        attachToState()
    }
    
    /// Retrieving all appointments from the service layer
    private func fetchAppointments() {
        service.fetchAll()
    }
    
    /// Attaching viewModel to State
    private func attachToState() {
        state.$appointmentsState.receive(on: RunLoop.main)
            .map(makeUIState)
            .assign(to: &$presentationState)
    }
    
    private func makeUIState(from state: EntriesState) -> EntriesUIState {
        switch state {
        case .loading(currentValue: let currentAppointments):
            return .loading(currentValue: self.sectionList(from: currentAppointments))
            
        case .loaded(let allAppointments):
            return .loaded(newValue: self.sectionList(from: allAppointments))
            
        case .failed(let error, let currentAppointments):
            return .failed(.failure(error.toString()), currentValue: self.sectionList(from: currentAppointments))
        }
    }
    
    private func sectionList(from appointments: [Appointment]?) -> [AppointmentSectionUIModel]? {
        guard let appointments = appointments else {
            return nil
        }
        /// Sorting all appointments based on their "date"
        let sortedAppointments = appointments.sorted(by: <)
        
        /// Grouping all appointments based on their computed property "designatedSection" into a dictionary
        /// Dictionary keys = Section Titles
        let entriesGroupedBySection = Dictionary(grouping: sortedAppointments) { $0.designatedSection }
        
        /// Sorting dictionary based on its keys
        let entriesSortedBySection = entriesGroupedBySection.sorted {$0.key.rawValue < $1.key.rawValue}
        
        var newSections: [AppointmentSectionUIModel] = []
        
        /// Parsing the newly created dictionary
        /// For each key, create the afferent section
        for (sectionTitle, sectionAppointments) in entriesSortedBySection {
            let uiModels = sectionAppointments.map { sectionAppointment in
                mapper.convertToUIModel(from: sectionAppointment)
            }
            let section = AppointmentSectionUIModel(title: sectionTitle.toString(), items: uiModels)
            newSections.append(section)
        }
        
        return newSections
    }
}

// TODO: change to Domain Model when introducing Repository/Servic
extension Appointment {
    /// Introducing a computed property which indicates the section which an appointment belongs to based on its "date"
    var designatedSection: AppointmentsViewModel.Section {
        if Calendar.current.isDateThisWeek(date) {
            return .thisWeek
        }
        else if Calendar.current.isDateThisMonth(date) {
            return .thisMonth
        }
        else if Calendar.current.isDateThisYear(date) {
            return .thisYear
        }
        else {
            return .upcoming
        }
//        else {
//            return .previous
//        }
    }
}

enum AppointmentPresentationError: LocalizedError {
    case failure(String)
    
    var errorDescription: String? {
        return "Error"
    }
    
    var failureReason: String? {
        switch self {
        case .failure(let reason):
            return reason
        }
    }
}
