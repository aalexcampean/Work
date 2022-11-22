//
//  SupportGroupsService.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 29.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

protocol SupportGroupsService {
  func addEvent(event: SupportGroupEvent)
  func updateEvent(updatedEvent: SupportGroupEvent)
  func deleteEvent(event: SupportGroupEvent)
  func fetchAllSupportGroupEvents()
}
