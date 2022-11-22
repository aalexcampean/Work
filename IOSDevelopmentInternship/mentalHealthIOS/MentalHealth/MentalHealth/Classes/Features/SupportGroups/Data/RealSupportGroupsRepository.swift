//
//  RealSupportGroupsRepository.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 05.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation
import Combine
import Alamofire

struct RealSupportGroupsRepository: SupportGroupsRepository {
  
  // MARK: - Dependencies
  
  private let session: Alamofire.Session
  private let mapper: SupportGroupsDTOMapper
  
  // MARK: - Configuration
  
  private let baseURL = "https://support-groups-mh.nexttech.ro/api/groups/"
  private let loggedUserIdentifier = "1"
  
  // MARK: - Init
  
  init(session: Alamofire.Session,
       mapper: SupportGroupsDTOMapper) {
    self.session = session
    self.mapper = mapper
  }
  
  func add(event: SupportGroupEvent) -> AnyPublisher<SupportGroupEvent, RepositoryError> {
    let eventDTO = mapper.convertToDTO(from: event)
    return session.request(baseURL,
                           method: .post,
                           parameters: eventDTO,
                           encoder: JSONParameterEncoder.default)
      .validate()
      .publishDecodable(type: SupportGroupsDTOs.EventResponse.self)
      .tryCustomMap(mapper.convertToEvent)
      .eraseToAnyPublisher()
  }
  
  func update(updatedEvent: SupportGroupEvent) -> AnyPublisher<SupportGroupEvent, RepositoryError> {
    let updateURL = "\(baseURL)\(updatedEvent.identifier)"
    debugPrint(updateURL)
    return session.request(updateURL,
                           method: .put,
                           parameters: loggedUserIdentifier,
                           encoder: JSONParameterEncoder.default)
      .validate()
      .publishDecodable()
      .tryCustomMap(mapper.convertToEvent)
      .eraseToAnyPublisher()
  }
  
  func delete(event: SupportGroupEvent) -> AnyPublisher<SupportGroupEvent, RepositoryError> {
    let deleteURL = "\(baseURL)\(event.identifier)"
    return session.request(deleteURL, method: .delete)
          .validate()
          .publishDecodable(type: SupportGroupsDTOs.EventResponse.self)
          .tryCustomMap(mapper.convertToEvent)
          .eraseToAnyPublisher()
  }
  
  func getAllEventsPublisher() -> AnyPublisher<[SupportGroupEvent], RepositoryError> {
    let getAllEventsURL = "\(baseURL)?userId=\(loggedUserIdentifier)"
    return session.request(getAllEventsURL, method: .get)
      .validate()
      .publishDecodable(type: [SupportGroupsDTOs.EventResponse].self)
      .tryCustomMap(mapper.convertToEventsArray)
      .eraseToAnyPublisher()
  }
}
