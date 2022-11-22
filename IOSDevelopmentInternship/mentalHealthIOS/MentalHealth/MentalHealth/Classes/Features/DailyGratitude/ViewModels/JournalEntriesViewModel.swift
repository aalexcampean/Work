//
//  JournalEntryViewModel.swift
//  MentalHealth
//
//  Created by alexcampean on 22.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation
import Combine

/// Used for the list titles and their string representation
enum TitleGroup: Int {
  case thisWeek
  case thisMonth
  case previous
  
  func toString() -> String {
    switch self {
    case .thisWeek:
      return NSLocalizedString("gratitudeJournal.list.section.thisWeek", comment: "")
    case .thisMonth:
      return NSLocalizedString("gratitudeJournal.list.section.thisMonth", comment: "")
    case .previous:
      return NSLocalizedString("gratitudeJournal.list.section.previous", comment: "")
    }
  }
}

enum DailyGratitudePresentationError: LocalizedError {
  case failure(String)
  
  var errorDescription: String? {
    return NSLocalizedString("gratitudeJournal.list.error.title", comment: "")
  }
  
  var failureReason: String? {
    switch self {
    case .failure(let reason):
      return reason
    }
  }
}

class JournalEntriesViewModel: ObservableObject {
  // MARK: Type Alias for the 2 types of LoadingState
  typealias EntryState = LoadingState<[DailyGratitudeJournalEntry], RepositoryError>
  typealias EntryUIState = LoadingState<[JournalEntrySectionUIModel], DailyGratitudePresentationError>
  
  // MARK: Published properties
  @Published private(set) var presentationState: EntryUIState = .loading()
  
  // MARK: Date formatter
  private var dateFormatter = DateFormatter()
  
  // MARK: Subscriptions array
  private var cancellables = Set<AnyCancellable>()
  
  // MARK: Dependencies
  private var service: DailyGratitudeService
  private var state: DailyGratitudeState
  
  // MARK: Constants
  let listTitle = NSLocalizedString("gratitudeJournal.list.title", comment: "")
  let emptyListText = NSLocalizedString("gratitudeJournal.list.emptyList.message", comment: "")
  let carouselImages = [ImageSource.url(URL(string: "https://images.unsplash.com/photo-1489996833391-87afa2532240?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=2340&q=80")!),
                        ImageSource.url(URL(string: "https://images.unsplash.com/photo-1575050312925-f0d7757591eb?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=987&q=80")!),
                        ImageSource.url(URL(string: "https://images.unsplash.com/photo-1533558837877-f9a97ac5ba0c?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=1364&q=80")!),
                        ImageSource.url(URL(string: "https://images.unsplash.com/photo-1547626740-02cb6aed9ef8?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=2340&q=80")!)]
  
  init(service: DailyGratitudeService, state: DailyGratitudeState) {
    self.service = service
    self.state = state
    
    /// The date format required for Journal Entries is Month-Day-Year
    dateFormatter.dateFormat = "MMMM dd yyyy"
    fetchJournalEntries()
    
    // MARK: Setup
    attachToState()
  }
  
  /// Attaching viewModel to State
  private func attachToState() {
    state.$journalState.receive(on: RunLoop.main)
      .map(makeUIState)
      .assign(to: &$presentationState)
  }
  
  /// Retrieving all journal entries from the service layer
  private func fetchJournalEntries() {
    service.fetchAllJournalEntries()
  }
  
  private func makeUIState(from state: EntryState) -> EntryUIState {
    switch state {
    case .loading(currentValue: let currentEntries):
      return .loading(currentValue: self.makeListWithSections(from: currentEntries))
      
    case .loaded(let newEntries):
      return .loaded(newValue: self.makeListWithSections(from: newEntries))
      
    case .failed(let error, let currentEntries):
      return .failed(.failure(error.toString()),
                     currentValue: self.makeListWithSections(from: currentEntries))
    }
  }
  
  private func makeListWithSections(from entries: [DailyGratitudeJournalEntry]?)
  -> [JournalEntrySectionUIModel]? {
    guard let entries = entries else {
      return nil
    }
    /// Sorting all entries based on their "publicationDate"
    let sortedEntries = entries.sorted(by: >)
    
    /// Grouping all entries based on their computed property "designatedSection" into a dictionary
    /// Dictionary keys = Section Titles
    let entriesGroupedBySection = Dictionary(grouping: sortedEntries) { $0.designatedSection }
    /// Sorting dictionary based on its keys
    /// Dictionary keys = Section Titles
    let entriesSortedBySection = entriesGroupedBySection.sorted {$0.key.rawValue < $1.key.rawValue}
    
    var newSections: [JournalEntrySectionUIModel] = []
    
    /// Parsing the newly created dictionary
    /// For each key, create the afferent section
    for (sectionTitle, sectionEntries) in entriesSortedBySection {
      let uiModels = sectionEntries.map { sectionEntry in
        self.mapToUIModel(from: sectionEntry)
      }
      let section = JournalEntrySectionUIModel(title: sectionTitle.toString(), items: uiModels)
      newSections.append(section)
    }
    
    return newSections
  }
  
  /// Mapping a domainModel into a UIModel
  private func mapToUIModel(from entry: DailyGratitudeJournalEntry) -> JournalEntryUIModel {
    var image: ImageSource = .placeholder
    /// Validating the image and the url, If not valid, we use a placeholder
    if let validImage = entry.image, let validUrl = URL(string: validImage) {
      image = .url(validUrl)
    }
    
    var finalTags: [TagUIModel] = []
    if let tagsUnwrapper: [TagUIModel] = entry.associatedTags.map({ $0.map { tagItem in
      self.makeTagUIModel(from: tagItem)
    }}) {
      finalTags = tagsUnwrapper
    }
      
    return JournalEntryUIModel(id: entry.identifier,
                               title: entry.title,
                               image: image,
                               publicationDate: self.dateFormatter.string(from: entry.publicationDate),
                               tags: finalTags,
                               associatedImages: self.carouselImages)
  }
  
  /// Mapping a tag domainModel into a UIModel
  private func makeTagUIModel(from tagItem: TagItem) -> TagUIModel {
    TagUIModel(id: tagItem.id,
               text: tagItem.text,
               isSelected: false)
  }
  
  /// Temporary function for showcasing the loading behavior.
  func refresh() {
    fetchJournalEntries()
  }
  
  /// Temporary function for showcasing the add entry behavior.
  func addEntry() {
    let entry = DailyGratitudeJournalEntry(identifier: "10",
                                           title: "new entry",
                                           image: nil,
                                           publicationDate: Date.now.subtractedRandomly(),
                                           tags: ["new", "gratitude"])
    service.addJournalEntry(journalEntry: entry)
  }
}

/// Extending DailyGratitudeJournalEntry
extension DailyGratitudeJournalEntry {
  /// Introducing a computed property which indicated the section which an entry belongs to based on its "publicationDate"
  var designatedSection: TitleGroup {
    if Calendar.current.isDateThisWeek(publicationDate) {
      return .thisWeek
    }
    else if Calendar.current.isDateThisMonth(publicationDate) &&
              !Calendar.current.isDateThisWeek(publicationDate) {
      return .thisMonth
    }
    else {
      return .previous
    }
  }
}

/// Extending RepositoryError
extension RepositoryError {
  /// Returns the string representation of an error
  func toString() -> String{
    switch self {
    case .internalFailure:
      return NSLocalizedString("gratitudeJournal.list.error.loading", comment: "")
    case .noInternet:
      return NSLocalizedString("gratitudeJournal.list.error.noInternet", comment: "")
    case .entryNotFound:
      return NSLocalizedString("gratitudeJournal.list.error.notFound", comment: "")
    case .serverError(let serverError):
      return serverError
    }
  }
}
