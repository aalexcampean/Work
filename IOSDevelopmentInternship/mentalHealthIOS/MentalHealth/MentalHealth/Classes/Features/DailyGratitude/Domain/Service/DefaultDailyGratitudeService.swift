//
//  DefaultDailyGratitudeService.swift
//  MentalHealth
//
//  Created by alexcampean on 29.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation
import Combine
import SwiftUI

typealias JournalEntriesAndTags = (journalEntries: [DailyGratitudeJournalEntry], tags: TagsDictionary)

class DefaultDailyGratitudeService: DailyGratitudeService {
  // MARK: - Dependencies
  private var journalEntriesrepository: DailyGratitudeRepository
  private var tagsRepository: TagsRepository
  // MARK: - Private State
  private var state: DailyGratitudeState
  // MARK: - Subcriptions
  private lazy var subscriptions: [AnyCancellable] = []
  
  init(repository: DailyGratitudeRepository, tagsRepository: TagsRepository, state: DailyGratitudeState) {
    self.journalEntriesrepository = repository
    self.tagsRepository = tagsRepository
    self.state = state
  }
  
  func addJournalEntry(journalEntry: DailyGratitudeJournalEntry) {
    beginLoading()
    
    let addPublisher = self.journalEntriesrepository.add(journalEntry: journalEntry)
    
    addPublisher.sink(receiveCompletion: { completion in
      switch completion {
      case .finished:
        debugPrint("Journal Entry added successfully")
        
      case .failure(let addError):
        debugPrint("Add Operation failed: \(addError)")
        self.endLoading(error: addError)
      }
    }, receiveValue: { entry in
      var entries = self.state.journalState.currentValue
      entries?.append(journalEntry)
      self.endLoading(entries: entries)
    }).store(in: &subscriptions)
  }
  
  func updateJournalEntry(journalEntry: DailyGratitudeJournalEntry) {
    beginLoading()
    
    let updatePublisher = self.journalEntriesrepository.update(journalEntry: journalEntry)
    
    updatePublisher.sink(receiveCompletion: { completion in
      switch completion {
      case .finished:
        debugPrint("Journal Entry updated successfully")
        
      case .failure(let updateError):
        debugPrint("Update Operation failed: \(updateError)")
        self.endLoading(error: updateError)
      }
    }, receiveValue: { entry in
      var entries = self.state.journalState.currentValue
      guard let index = entries?.firstIndex(of: entry) else {
        self.endLoading(error: .entryNotFound)
        return
      }
      entries?[index] = journalEntry
      self.endLoading(entries: entries)
    }).store(in: &subscriptions)
  }
  
  func deleteJournalEntry(journalEntry: DailyGratitudeJournalEntry) {
    beginLoading()
    
    let deletePublisher = self.journalEntriesrepository.delete(journalEntry: journalEntry)
    
    deletePublisher.sink(receiveCompletion: { completion in
      switch completion {
      case .finished:
        debugPrint("Journal Entry deleted successfully")
        
      case .failure(let deleteError):
        debugPrint("Delete Operation failed: \(deleteError)")
        self.endLoading(error: deleteError)
      }
    }, receiveValue: { entry in
      var entries = self.state.journalState.currentValue
      guard let index = entries?.firstIndex(of: entry) else {
        self.endLoading(error: .entryNotFound)
        return
      }
      entries?.remove(at: index)
      self.endLoading(entries: entries)
    }).store(in: &subscriptions)
  }
  
  func fetchAllJournalEntries() {
    beginLoading()
    
    let journalEntriesPublisher = self.journalEntriesrepository.getAllJournalEntriesPublisher()
    let tagsPublisher = self.tagsRepository.getAllTagsPublisher()
    
    Publishers.CombineLatest(journalEntriesPublisher, tagsPublisher)
      .map(mapToJournalEntry)
      .eraseToAnyPublisher()
      .sink(receiveCompletion: handleFetchAllCompletion, receiveValue: handleFetchAllValue)
      .store(in: &subscriptions)
  }
  
  // MARK: - Private Properties
  private func mapToJournalEntry(journalEntriesAndTags: JournalEntriesAndTags) -> [DailyGratitudeJournalEntry]{
    let tags = journalEntriesAndTags.tags
    return journalEntriesAndTags.journalEntries.map{ associateTagsToJournalEntry($0, tags: tags) }
  }
  
  private func associateTagsToJournalEntry(_ entry: DailyGratitudeJournalEntry, tags: TagsDictionary) -> DailyGratitudeJournalEntry {
    var newEntry = entry
    newEntry.associatedTags = matchTagsWithIds(tagsDict: tags, ids: entry.tags)
    return newEntry
  }
  
  private func matchTagsWithIds(tagsDict: TagsDictionary, ids: [TagID]) -> [TagItem] {
    var result: [TagItem] = []
    for tagId in tagsDict.keys {
      if ids.contains(tagId), let tagText = tagsDict[tagId]{
        result.append(tagText)
      }
    }
    return result
  }
  
  private func handleFetchAllCompletion(completion: Subscribers.Completion<RepositoryError>) {
    switch completion {
    case .finished:
      debugPrint("Journal Entries fetched successfully")
      
    case .failure(let fetchError):
      debugPrint("Fetch Operation failed: \(fetchError)")
      self.endLoading(error: fetchError)
    }
  }
  
  private func handleFetchAllValue(value: [DailyGratitudeJournalEntry]) {
    self.endLoading(entries: value)
  }
  
  private func beginLoading() {
    state.journalState = .loading(currentValue: state.journalState.currentValue)
  }
  
  private func endLoading(entries: [DailyGratitudeJournalEntry]?) {
    state.journalState = .loaded(newValue: entries)
  }
  
  private func endLoading(error: RepositoryError) {
    state.journalState = .failed(error, currentValue: state.journalState.currentValue)
  }
}
