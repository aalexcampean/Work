//
//  DailyGratitudeServerRepository.swift
//  MentalHealth
//
//  Created by alexcampean on 11.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation
import Combine
import Alamofire

class DailyGratitudeServerRepository: DailyGratitudeRepository {
  // MARK: - Private Properties
  private struct ServerInfo {
    static let getJournalEntriesEndpoint = "https://gratitude-mh.nexttech.ro/api/messages/"
    static let userID = "2"
  }
  private let session: Alamofire.Session
  private let journalEntryDTOMapper: JournalEntryDTOMapper
  
  init(session: Alamofire.Session, mapper: JournalEntryDTOMapper) {
    self.session = session
    self.journalEntryDTOMapper = mapper
  }
  
  func add(journalEntry: DailyGratitudeJournalEntry) -> JournalEntryPublisher {
    return Future<DailyGratitudeJournalEntry, RepositoryError> { promise in
      promise(.success(journalEntry))
    }.eraseToAnyPublisher()
  }
  
  func delete(journalEntry: DailyGratitudeJournalEntry) -> JournalEntryPublisher {
    return Future<DailyGratitudeJournalEntry, RepositoryError> { promise in
      promise(.success(journalEntry))
    }.eraseToAnyPublisher()
  }
  
  func update(journalEntry: DailyGratitudeJournalEntry) -> JournalEntryPublisher {
    return Future<DailyGratitudeJournalEntry, RepositoryError> { promise in
      promise(.success(journalEntry))
    }.eraseToAnyPublisher()
  }
  
  func getAllJournalEntriesPublisher() -> JournalEntriesPublisher {
    let getUserJournalEntriesURL = "\(ServerInfo.getJournalEntriesEndpoint)\(ServerInfo.userID)"
    return session.request(getUserJournalEntriesURL, method: .get)
      .validate()
      .publishDecodable(type: [DailyGratitudeDTOs.Response].self)
      .tryCustomMap(journalEntryDTOMapper.makeJournalEntries)
      .eraseToAnyPublisher()
  }
}
