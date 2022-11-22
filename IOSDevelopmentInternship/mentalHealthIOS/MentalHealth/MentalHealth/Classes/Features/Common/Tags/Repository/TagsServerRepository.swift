//
//  TagsServerRepository.swift
//  MentalHealth
//
//  Created by alexcampean on 07.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation
import Combine
import Alamofire

typealias TagsDictionary = Dictionary<String, TagItem>

class TagsServerRepository: TagsRepository {
  // MARK: - Private Properties
  private struct ServerInfo {
    static let getTagsEndpoint = "https://support-groups-mh.nexttech.ro/api/tags"
  }
  private let session: Alamofire.Session
  private var tagItems: [TagItem] = []
  private let tagDTOMapper: TagsDTOMapper
  
  init (session: Alamofire.Session, mapper: TagsDTOMapper) {
    self.session = session
    self.tagDTOMapper = mapper
  }
  
  func add(tag: TagItem) -> TagPublisher {
    return Future<TagItem, RepositoryError> { promise in
      self.tagItems.append(tag)
      promise(.success(tag))
    }.eraseToAnyPublisher()
  }
  
  func delete(tag: TagItem) -> TagPublisher {
    return Future<TagItem, RepositoryError> { promise in
      guard let index = self.tagItems.firstIndex(of: tag) else {
        promise(.failure(.entryNotFound))
        return
      }
      self.tagItems.remove(at: index)
      promise(.success(tag))
    }.eraseToAnyPublisher()
  }
  
  func update(tag: TagItem) -> TagPublisher {
    return Future<TagItem, RepositoryError> { promise in
      guard let index = self.tagItems.firstIndex(of: tag) else {
        promise(.failure(.entryNotFound))
        return
      }
      self.tagItems[index] = tag
      promise(.success(tag))
    }.eraseToAnyPublisher()
  }
  
  func getAllTagsPublisher() -> TagsPublisher {
    return session.request(ServerInfo.getTagsEndpoint, method: .get)
      .validate()
      .publishDecodable(type: [TagDTOs.Response].self)
      .tryCustomMap(tagDTOMapper.makeTagItems)
      .eraseToAnyPublisher()
  }
}
