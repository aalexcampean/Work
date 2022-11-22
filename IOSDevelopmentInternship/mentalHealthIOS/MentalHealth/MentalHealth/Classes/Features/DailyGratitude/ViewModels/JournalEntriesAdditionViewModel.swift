//
//  JournalEntriesAdditionViewModel.swift
//  MentalHealth
//
//  Created by alexcampean on 19.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation
import Combine
import SwiftUI

class JournalEntriesAdditionViewModel: ObservableObject {
  // MARK: - Published properties
  @Published var inputMessage: String = ""
  @Published var isTextFieldSelected: Bool = false
  @Published var tagsUI: [TagUIModel] = [TagUIModel(id: "1", text: "happiness"),
                                         TagUIModel(id: "2",text: "inspired"),
                                         TagUIModel(id: "3", text: "motivation"),
                                         TagUIModel(id: "4", text: "pride"),
                                         TagUIModel(id: "5", text: "excitement"),
                                         TagUIModel(id: "6", text: "health"),
                                         TagUIModel(id: "7", text: "surprise"),
                                         TagUIModel(id: "8", text: "life"),
                                         TagUIModel(id: "9", text: "courage"),
                                         TagUIModel(id: "10", text: "energised")]
  // MARK: - Constants
  let addNewEntryTitle = NSLocalizedString("gratitudeJournal.add.newEntry.title", comment: "")
  let textPrompt = NSLocalizedString("gratitudeJournal.add.newEntry.textPrompt", comment: "")
  let buttonTitle = NSLocalizedString("gratitudeJournal.add.newEntry.buttonTitle", comment: "")
  
  // MARK: - Private properties
  private var service: DailyGratitudeService
  private var state: DailyGratitudeState
  
  init(service: DailyGratitudeService, state: DailyGratitudeState) {
    self.service = service
    self.state = state
  }
  
  func selectTag(tagUiModel: TagUIModel) {
    guard let index = tagsUI.firstIndex(of: tagUiModel) else {
      return
    }
    var removedTag = tagsUI.remove(at: index)
    removedTag.isSelected.toggle()
    
    tagsUI.insert(removedTag, at: index)
  }
  
  func selectTextField() {
    isTextFieldSelected.toggle()
  }
  
  func saveJournalEntry() {
    let newJournalEntry = createJournalEntry()
    service.addJournalEntry(journalEntry: newJournalEntry)
  }
  
  private func createJournalEntry() -> DailyGratitudeJournalEntry {
    let tagList = tagsUI.filter{ $0.isSelected }
      .map { tagUIModel in
        TagItem(id: tagUIModel.id, text: tagUIModel.text)
      }
    
    return DailyGratitudeJournalEntry(identifier: UUID().uuidString,
                                      title: inputMessage,
                                      image: "https://images.unsplash.com/photo-1575050312925-f0d7757591eb?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=987&q=80",
                                      publicationDate: Date.now,
                                      tags: [],
                                      associatedTags: tagList)
  }
}
