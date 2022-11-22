//
//  SupportGroupsRepository.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 25.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation
import Combine

protocol SupportGroupsRepository {
  func add(event: SupportGroupEvent) -> AnyPublisher<SupportGroupEvent, RepositoryError>
  func update(updatedEvent: SupportGroupEvent) -> AnyPublisher<SupportGroupEvent, RepositoryError>
  func delete(event: SupportGroupEvent) -> AnyPublisher<SupportGroupEvent, RepositoryError>
  func getAllEventsPublisher() -> AnyPublisher<[SupportGroupEvent], RepositoryError>
}
