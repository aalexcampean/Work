//
//  SupportGroupEventDetailsViewModel.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 12.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation
import EventKit
import CoreLocation

class SupportGroupEventDetailsViewModel: ObservableObject {
  
  // MARK: - Published Properties
  
  @Published private(set) var presentationState: LoadingState<SupportGroupItemUIModel, SupportGroupsPresentationError> = .loading()
  
  // MARK: - Public Properties
  
  let aboutSectionTitle = NSLocalizedString("supportGroups.list.item.about.title", comment: "")
  let occurrence = NSLocalizedString("supportGroups.list.item.details.occurrence", comment: "")
  let participantsTitle = NSLocalizedString("supportGroups.list.item.participants.title", comment: "")
  
  // MARK: - Private Properties
  private var service: SupportGroupsService
  private var state: SupportGroupsState
  private var mapper: SupportGroupsUIMapper
  private let eventID: String
  private let geocoder: CLGeocoder
  
  // MARK: - Init
  
  init(service: SupportGroupsService,
       state: SupportGroupsState,
       mapper: SupportGroupsUIMapper,
       geocoder: CLGeocoder,
       eventID: String) {
    self.service = service
    self.state = state
    self.mapper = mapper
    self.geocoder = geocoder
    self.eventID = eventID
    
    attachToState()
  }
  
  // MARK: - Attach to state
  
  private func attachToState() {
    state.$eventsState.receive(on: RunLoop.main)
      .map({ loadingState -> LoadingState<SupportGroupItemUIModel, SupportGroupsPresentationError> in
        
        guard let currentEvents = loadingState.currentValue else {
          return .failed(.failure(""))
        }
        
        guard let currentEvent = currentEvents.first(where: { $0.identifier == self.eventID }) else {
          return .failed(.failure(""))
        }
        
        switch loadingState {
        case .loading:
          return .loading(currentValue: self.mapper.convertToUIModel(from: currentEvent,
                                                                     participants: self.mockedImageSources()))
          
        case .loaded:
          return .loaded(newValue: self.mapper.convertToUIModel(from: currentEvent,
                                                                participants: self.mockedImageSources()))
          
        case .failed(let error, _):
          let message: String
          switch error {
          case .noInternet:
            message = "No Internet Connection"
          case .internalFailure:
            message = "Internal Failure"
          case .entryNotFound:
            message = "Support Groups Event Not Found"
          case .serverError(let error):
            message = error
          }
          
          return .failed(.failure(message),
                         currentValue: self.mapper.convertToUIModel(from: currentEvent,
                                                                    participants: self.mockedImageSources()))
        }
      })
      .assign(to: &$presentationState)
  }
  
  func requestCalendarAccess() {
    let eventStore = EKEventStore()
    if EKEventStore.authorizationStatus(for: .event) == .authorized {
      createCalendarEvent(eventStore: eventStore)
    } else {
      eventStore.requestAccess(to: .event) { (granted, error) in
        guard granted else {
          return
        }
        self.createCalendarEvent(eventStore: eventStore)
      }
    }
  }
  
  private func createCalendarEvent(eventStore: EKEventStore) {
    guard let calendar = eventStore.defaultCalendarForNewEvents,
          let validJournalEntry = self.state.eventsState.currentValue?
            .first(where: { $0.identifier == self.eventID }) else { return }
    
    let event = EKEvent(eventStore: eventStore)
    event.title = validJournalEntry.title
    event.startDate = validJournalEntry.startDateAndTime
    event.isAllDay = false
    event.endDate = validJournalEntry.startDateAndTime.addingTimeInterval(60 * 60)
    event.calendar = calendar
    
    do {
      try eventStore.save(event, span: .thisEvent, commit: true)
    } catch let error as NSError {
      debugPrint("error : \(error)")
    }
  }
  
  func handleJoinButtonPress() {
    let currentValues = state.eventsState.currentValue
    if var validCurrentValues = currentValues {
      let index = validCurrentValues.firstIndex(where: { $0.identifier == self.eventID })
      guard let validIndex = index else {
        return
      }
      validCurrentValues[validIndex].isJoined.toggle()
      service.updateEvent(updatedEvent: validCurrentValues[validIndex])
    }
  }
  
  func getLocationURL(locationString: String, completionHandler: @escaping (String) -> Void) {
    var locationURL: URL? = nil
    geocoder.geocodeAddressString(locationString) { placemarks, error in
      guard error == nil,
            let placemark = placemarks?.first,
            let latitude = placemark.location?.coordinate.latitude,
            let longitude = placemark.location?.coordinate.longitude else {
              return
            }
      
      let url = "maps://?daddr=\(latitude),\(longitude)"
      
      locationURL = URL(string: url)
      
      let currentState = self.presentationState.currentValue
      
      if var currentState = currentState {
        currentState.link = locationURL
        self.presentationState = .loaded(newValue: currentState)
      }
      
      completionHandler(url)
    }
  }
  
  func handleBookmarkButtonPress() {
    guard let events = state.eventsState.currentValue,
          let index = events.firstIndex(where: { $0.identifier == eventID }) else {
            return
          }
    
    var event = events[index]
    event.isBookmarked.toggle()
    service.updateEvent(updatedEvent: event)
  }
}

// MARK: - Mocked Image Sources

extension SupportGroupEventDetailsViewModel {
  func mockedImageSources() -> [ImageSource] {
    let mockedImageSources = [ImageSource.url(URL(string: "https://images.unsplash.com/photo-1529068755536-a5ade0dcb4e8?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=881&q=80")!),
                              ImageSource.url(URL(string: "https://images.unsplash.com/photo-1570295999919-56ceb5ecca61?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=880&q=80")!),
                              
                              ImageSource.url(URL(string: "https://images.unsplash.com/photo-1527980965255-d3b416303d12?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=880&q=80")!),
                              
                              ImageSource.url(URL(string: "https://images.unsplash.com/photo-1520451644838-906a72aa7c86?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=850&q=80")!),
                              
                              ImageSource.url(URL(string: "https://images.unsplash.com/photo-1499887142886-791eca5918cd?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=880&q=80")!),
                              
                              ImageSource.url(URL(string: "https://images.unsplash.com/photo-1523983254932-c7e6571c9d60?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=902&q=80")!)]
    return mockedImageSources
  }
}
