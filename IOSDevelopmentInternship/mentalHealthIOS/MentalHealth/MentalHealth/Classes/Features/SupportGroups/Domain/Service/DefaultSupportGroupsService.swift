//
//  DefaultSupportGroupsService.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 29.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation
import Combine

typealias EventsAndTags = (events: [SupportGroupEvent], tags: TagsDictionary)

class DefaultSupportGroupsService: SupportGroupsService {
  
  // MARK: - Private Properties
  
  private var eventsRepository: SupportGroupsRepository
  private var tagsRepository: TagsRepository
  private var state: SupportGroupsState
  private var subscriptions: [AnyCancellable] = []
  
  // MARK: - Init
  
  init(supportGroupsState: SupportGroupsState,
       supportGroupsRepository: SupportGroupsRepository,
       tagsRepository: TagsRepository) {
    self.state = supportGroupsState
    self.eventsRepository = supportGroupsRepository
    self.tagsRepository = tagsRepository
  }
  
  // MARK: - SupportGroupsService
  
  func addEvent(event: SupportGroupEvent) {
    self.beginLoading()
    let addPublisher = eventsRepository.add(event: event)
    addPublisher.sink(receiveCompletion: { completion in
      switch completion {
      case .finished:
        debugPrint("Succes: The event was added")
      case .failure(let addError):
        debugPrint("Addition Operation failed: \(addError)")
        self.endLoading(error: addError)
      }
    }, receiveValue: { event in
      var events = self.state.eventsState.currentValue
      events?.append(event)
      self.endLoading(events: events)
    }).store(in: &subscriptions)
  }
  
  func updateEvent(updatedEvent: SupportGroupEvent) {
    beginLoading()
    let updatePublisher = eventsRepository.update(updatedEvent: updatedEvent)
    updatePublisher.sink(receiveCompletion: { completion in
      switch completion {
      case .finished:
        debugPrint("Succes: The event was updated")
      case .failure(let updateError):
        debugPrint("Update Operation failed: \(updateError)")
        self.endLoading(error: updateError)
      }
    }, receiveValue: { event in
      var events = self.state.eventsState.currentValue
      guard let index = events?.firstIndex(of: event) else {
        self.endLoading(error: .entryNotFound)
        return
      }
      events?[index] = event
      self.endLoading(events: events)
    })
      .store(in: &subscriptions)
  }
  
  func deleteEvent(event: SupportGroupEvent) {
    beginLoading()
    let deletePublisher = eventsRepository.delete(event: event)
    deletePublisher.sink(receiveCompletion: { completion in
      switch completion {
      case .finished:
        debugPrint("Succes: Event deleted successfuly!")
      case .failure(let deleteError):
        debugPrint("Delete Operation failed: \(deleteError)")
        self.endLoading(error: deleteError)
      }
    }, receiveValue: { event in
      var events = self.state.eventsState.currentValue
      guard let index = events?.firstIndex(of: event) else {
        self.endLoading(error: .entryNotFound)
        return
      }
      events?.remove(at: index)
      self.endLoading(events: events)
    })
      .store(in: &subscriptions)
  }
  
  func fetchAllSupportGroupEvents() {
    beginLoading()
    
    let eventsPublisher = eventsRepository.getAllEventsPublisher()
    let tagsPublisher = self.tagsRepository.getAllTagsPublisher()
    Publishers.CombineLatest(eventsPublisher, tagsPublisher)
      .map(mapToEvent)
      .eraseToAnyPublisher()
      .sink(receiveCompletion: handleFetchAllCompletion, receiveValue: handleFetchAllValue)
      .store(in: &subscriptions)
  }
  
  private func mapToEvent(eventsAndTags: EventsAndTags) -> [SupportGroupEvent] {
    let tags = eventsAndTags.tags
    return eventsAndTags.events.map { event in
      var newEvent = event
      var finalTags: [TagItem] = []
      event.tags.forEach { tagId in
        guard let tag = tags[tagId] else {
          return
        }
        finalTags.append(tag)
      }
      newEvent.associatedTags = finalTags
      return newEvent
    }
  }
  
  private func handleFetchAllCompletion(completion: Subscribers.Completion<RepositoryError>) {
    switch completion {
    case .finished:
      debugPrint("Events fetched successfully")
      
    case .failure(let fetchError):
      debugPrint("Fetch Operation failed: \(fetchError)")
      self.endLoading(error: fetchError)
    }
  }
  
  private func handleFetchAllValue(value: [SupportGroupEvent]) {
    self.endLoading(events: value)
  }
  
  private func beginLoading() {
    state.eventsState = .loading(currentValue: state.eventsState.currentValue)
  }
  
  private func endLoading(events: [SupportGroupEvent]?) {
    state.eventsState = .loaded(newValue: events)
  }
  
  private func endLoading(error: RepositoryError) {
    state.eventsState = .failed(error, currentValue: state.eventsState.currentValue)
  }
}
