//
//  DefaultSupportGroupsUIMapper.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 08.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation
import OrderedCollections

typealias Attribute = SupportGroupItemUIModel.Attribute

class DefaultSupportGroupsUIMapper: SupportGroupsUIMapper {
  
  /// This function converts domain model to ui model
  /// - Parameter event: A domain model of SupportGroupEvent type
  /// - Returns: An UI Model of SupportGroupItemUIModel
  func convertToUIModel(from event: SupportGroupEvent,
                        participants: [ImageSource] = []) -> SupportGroupItemUIModel {
    let title = event.title
    var image = ImageSource.placeholder
    
    if let validString = event.image, let validURL = URL(string: validString) {
      image = .url(validURL)
    }
    
    let startDate = DateFormattersStore.uiDateFormatter.string(from: event.startDateAndTime)
    let startDateExtended = DateFormattersStore.uiExtendedDateFormatter.string(from: event.startDateAndTime)
    
    let finalTags: [TagUIModel] = event.associatedTags.map(makeTagUIModel)
    
    var attributes = OrderedSet<SupportGroupItemUIModel.Attribute>()
    
    if event.isBookmarked {
      let bookmarkedString = NSLocalizedString("supportGroups.list.item.bookmarked", comment: "")
      attributes.append(Attribute.isBookmarked(bookmarkedString))
    }
    
    if event.isJoined {
      let joinedString = NSLocalizedString("supportGroups.list.item.joined", comment: "")
      attributes.append(Attribute.isJoined(joinedString))
    }
    
    var location = ""
    var linkURL: URL? = nil
    
    switch event.location {
    case .online(name: let receivedLocation, link: let link):
      location = receivedLocation
      linkURL = link
    case .onsite(name: let receivedLocation, location: let address):
      location = "\(address), \(receivedLocation)"
    }
    
    let unjoinString = NSLocalizedString("supportGroups.list.item.unjoin", comment: "")
    let joinString = NSLocalizedString("supportGroups.list.item.join", comment: "")
    let joinActionTitle = event.isJoined ? unjoinString : joinString
    
    let url = "calshow:\(event.startDateAndTime.timeIntervalSinceReferenceDate)"
    
    let uiModel = SupportGroupItemUIModel(id: event.identifier,
                                          title: title,
                                          image: image,
                                          startDate: startDate,
                                          startDateExtended: startDateExtended,
                                          location: location,
                                          link: linkURL,
                                          description: event.description,
                                          tags: finalTags,
                                          attributes: attributes,
                                          joinActionTitle: joinActionTitle,
                                          participants: participants,
                                          calendarUrl: url)
    return uiModel
  }
  
  private func makeTagUIModel(from tagItem: TagItem) -> TagUIModel {
    TagUIModel(id: tagItem.id,
               text: tagItem.text,
               isSelected: false)
  }
}
