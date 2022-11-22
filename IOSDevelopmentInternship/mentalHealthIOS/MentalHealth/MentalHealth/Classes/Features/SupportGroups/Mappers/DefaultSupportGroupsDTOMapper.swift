//
//  EventDTOMapper.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 08.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

typealias Location = SupportGroupEvent.Location

class DefaultSupportGroupsDTOMapper: SupportGroupsDTOMapper {
  
  func convertToEvent(from eventDTO: SupportGroupsDTOs.EventResponse) -> SupportGroupEvent {
    var date = Date.now
    if let validDate = DateFormattersStore.dtoDateFormatter.date(from: eventDTO.startDateAndTime) {
      date = validDate
    }
    
    var imageCoverURL: String? = nil
    if let validImage = eventDTO.image {
      imageCoverURL = validImage
    }
    
    var location: Location
    
    let onlineString = "online"
    
    if eventDTO.location == onlineString {
      location = .online(name: eventDTO.location, link: URL(string: eventDTO.address))
    } else {
      location = .onsite(name: eventDTO.location, location: eventDTO.address)
    }
    
    let event = SupportGroupEvent(identifier: eventDTO.id,
                                  title: eventDTO.title,
                                  image: imageCoverURL,
                                  startDateAndTime: date,
                                  location: location,
                                  description: eventDTO.description,
                                  tags: eventDTO.tags,
                                  associatedTags: [],
                                  isBookmarked: eventDTO.isBookmarked,
                                  isJoined: eventDTO.isJoined)
    return event
  }
  
  func convertToEventsArray(from eventDTOs: [SupportGroupsDTOs.EventResponse]) -> [SupportGroupEvent] {
    eventDTOs.map { convertToEvent(from: $0) }
  }
  
  func convertToDTO(from event: SupportGroupEvent) -> SupportGroupsDTOs.EventRequest {
    let title = event.title
    let date = DateFormattersStore.dtoDateFormatter.string(from: event.startDateAndTime)
    let tags = event.tags
    
    var location = ""
    var address = ""
    
    switch event.location {
    case .onsite(name: let name, location: let addressString):
      location = name
      address = addressString
    case .online(name: let name, link: let url):
      location = name
      if let url = url {
        address = url.absoluteString
      }
    }
    
    var imageString = ""
    
    if let imageStr = event.image {
      imageString = imageStr
    }
    
    let dto = SupportGroupsDTOs.EventRequest(id: event.identifier,
                                             title: title,
                                             image: imageString,
                                             location: location,
                                             address: address,
                                             description: event.description,
                                             startDateAndTime: date,
                                             tags: tags,
                                             isBookmarked: event.isBookmarked,
                                             isJoined: event.isJoined)
    return dto
  }
}
