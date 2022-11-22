//
//  SupportGroupsViewModel.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 23.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation
import Combine

enum SupportGroupsPresentationError: LocalizedError {
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

// MARK: - Main Type
class SupportGroupViewModel: ObservableObject {
  
  // MARK: - Published Properties
  
  @Published private(set) var presentationState: LoadingState<[SupportGroupSectionUIModel], SupportGroupsPresentationError> = .loading()
  
  // MARK: - Public Properties
  
  let listTitle = NSLocalizedString("supportGroups.list.title", comment: "")
  let searchbarHintText = NSLocalizedString("supportGroups.list.search.hintText", comment: "")
  
  let aboutSectionTitle = NSLocalizedString("supportGroups.list.item.about.title", comment: "")
  let occurrence = NSLocalizedString("supportGroups.list.item.details.occurrence", comment: "")
  let participantsTitle = NSLocalizedString("supportGroups.list.item.participants.title", comment: "")
  let emptyListText = NSLocalizedString("supportGroups.list.emptyList.message", comment: "")
  
  // MARK: - Private Properties
  
  private enum Section: CaseIterable {
    case thisWeek
    case thisMonth
    case upcoming
  }
  
  private var items: [SupportGroupEvent] = []
  private var cancellables = Set<AnyCancellable>()
  
  // MARK: - Dependencies
  
  private var service: SupportGroupsService
  private var state: SupportGroupsState
  private var mapper: SupportGroupsUIMapper
  
  // MARK: - Init
  
  init(service: SupportGroupsService,
       state: SupportGroupsState,
       mapper: SupportGroupsUIMapper) {
    self.service = service
    self.state = state
    self.mapper = mapper
    
    // Setup
    self.attachToState()
    
    fetchEvents()
  }
  
  // MARK: - Attach to state
  
  private func attachToState() {
    state.$eventsState.receive(on: RunLoop.main)
      .map({ loadingState -> LoadingState<[SupportGroupSectionUIModel], SupportGroupsPresentationError> in
        switch loadingState {
        case .loading(currentValue: let currentEvents):
          return .loading(currentValue: self.makeSections(from: currentEvents))
          
        case .loaded(let newEvents):
          return .loaded(newValue: self.makeSections(from: newEvents))
          
        case .failed(let error, let currentEvents):
          let message: String
          switch error {
          case .noInternet:
            message = NSLocalizedString("error.noInternet", comment: "")
          case .internalFailure:
            message = NSLocalizedString("supportGroups.list.error.loading", comment: "")
          case .entryNotFound:
            message = NSLocalizedString("supportGroups.item.error.notFound", comment: "")
          case .serverError(message: let msg):
            message = msg
          }
          return .failed(.failure(message),
                         currentValue: self.makeSections(from: currentEvents))
        }
      })
      .assign(to: &$presentationState)
  }
  
  // MARK: - Support Groups View-Model
  
  private func fetchEvents() {
    service.fetchAllSupportGroupEvents()
  }
  
  /// Filters a list by events' starting date and time
  /// - Parameter events: The list of events
  /// - Returns: A dictionary of Support Groups Events grouped by sections
  private func makeSections(from events: [SupportGroupEvent]?) -> [SupportGroupSectionUIModel]? {
    guard let events = events else {
      return nil
    }
    let sortedEvents = events.sorted(by: <)
    var timePeriods: [Section: [SupportGroupItemUIModel]] = [:]
    var sections: [SupportGroupSectionUIModel] = []
    
    sortedEvents.forEach({ event in
      guard Calendar.current.isDateInFuture(event.startDateAndTime) else {
        return
      }
      let timePeriod = self.getSection(of: event)
      let uiEvent = mapper.convertToUIModel(from: event,
                                            participants: [])
      if timePeriods[timePeriod] != nil {
        timePeriods[timePeriod]?.append(uiEvent)
      } else {
        timePeriods[timePeriod] = [uiEvent]
      }
    })
    
    Section.allCases.forEach({ section in
      guard let validSection = timePeriods[section] else {
        return
      }
      let uiSection = SupportGroupSectionUIModel(title: sectionTitle(for: section),
                                                 items: validSection)
      sections.append(uiSection)
    })
    
    return sections
  }
  
  /// Get the section the event belongs to
  /// - Parameter event: A support groups event
  /// - Returns: The section the event belongs to
  private func getSection(of event: SupportGroupEvent) -> Section {
    if Calendar.current.isDateThisWeek(event.startDateAndTime) {
      return .thisWeek
    }
    
    if Calendar.current.isDateThisMonth(event.startDateAndTime) {
      return .thisMonth
    }
    
    return .upcoming
  }
  
  /// Gets the localized string for a section
  /// - Parameter group: A section of events
  /// - Returns: The title of the section
  private func sectionTitle(for section: Section) -> String {
    switch section {
    case .thisWeek:
      return NSLocalizedString("supportGroups.list.section.thisWeek", comment: "")
    case .thisMonth:
      return NSLocalizedString("supportGroups.list.section.thisMonth", comment: "")
    case .upcoming:
      return NSLocalizedString("supportGroups.list.section.upcoming", comment: "")
    }
  }
}

// MARK: - Temporary functions
extension SupportGroupViewModel {
  func addEvent() {
    service.addEvent(event: SupportGroupEvent(identifier: UUID().uuidString,
                                              title: "New Event",
                                              image: "https://images.pexels.com/photos/775417/pexels-photo-775417.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1%27",
                                              startDateAndTime: Date.now.randomFutureDate(),
                                              location: .onsite(name: "Cluj-Napoca",
                                                                location: "Motilor, 6"),
                                              description: "Mental Health America (MHA)'s work is driven by its commitment to promote mental health as a critical part of overall wellness, including prevention services for all.",
                                              tags: ["1", "2"],
                                              associatedTags: [],
                                              isBookmarked: true,
                                              isJoined: true))
  }
  
  func deleteEvent() {
    service.deleteEvent(event: SupportGroupEvent(identifier: "1",
                                                 title: "New Event",
                                                 image: nil,
                                                 startDateAndTime: Date.now,
                                                 location: .onsite(name: "Cluj-Napoca",
                                                                   location: "Motilor, 6"),
                                                 description: "Description",
                                                 tags: ["test", "add"],
                                                 associatedTags: [],
                                                 isBookmarked: true,
                                                 isJoined: true))
  }
  
  func refresh() {
    fetchEvents()
  }
  
}
