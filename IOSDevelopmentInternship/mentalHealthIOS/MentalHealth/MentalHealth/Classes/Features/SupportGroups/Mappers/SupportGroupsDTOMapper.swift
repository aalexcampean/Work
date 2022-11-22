//
//  SupportGroupsDTOMapper.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 08.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

protocol SupportGroupsDTOMapper {
  func convertToEvent(from eventDTO: SupportGroupsDTOs.EventResponse) -> SupportGroupEvent
  func convertToEventsArray(from eventDTOs: [SupportGroupsDTOs.EventResponse]) -> [SupportGroupEvent]
  func convertToDTO(from event: SupportGroupEvent) -> SupportGroupsDTOs.EventRequest
}
