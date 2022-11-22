//
//  TagsMockedRepository.swift
//  MentalHealth
//
//  Created by alexcampean on 08.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation
import Combine

class TagsMockedRepository: TagsRepository {
  // MARK: - List of Tags
  private var tagItems: [TagItem]
  static let defaultTags = [TagItem(id: "1", text: "happiness"),
                            TagItem(id: "2",text: "inspired"),
                            TagItem(id: "3", text: "motivation"),
                            TagItem(id: "4", text: "pride"),
                            TagItem(id: "5", text: "excitement"),
                            TagItem(id: "6", text: "health"),
                            TagItem(id: "7", text: "surprise"),
                            TagItem(id: "8", text: "life"),
                            TagItem(id: "9", text: "courage"),
                            TagItem(id: "10", text: "energised")]
  
  // MARK: - Time interval for asynchronus operations
  private let timeInterval: TimeInterval
  
  init(interval: TimeInterval, tags: [TagItem] = defaultTags) {
    self.timeInterval = interval
    self.tagItems = tags
  }
  
  func add(tag: TagItem) -> TagPublisher {
    return Future<TagItem, RepositoryError> { promise in
      DispatchQueue.main.asyncAfter(deadline: .now() + self.timeInterval , execute: {
        self.tagItems.append(tag)
        promise(.success(tag))
      })
    }.eraseToAnyPublisher()
  }
  
  func delete(tag: TagItem) -> TagPublisher {
    return Future<TagItem, RepositoryError> { promise in
      DispatchQueue.main.asyncAfter(deadline: .now() + self.timeInterval , execute: {
        guard let index = self.tagItems.firstIndex(of: tag) else {
          promise(.failure(.entryNotFound))
          return
        }
        self.tagItems.remove(at: index)
        promise(.success(tag))
      })
    }.eraseToAnyPublisher()
  }
  
  func update(tag: TagItem) -> TagPublisher {
    return Future<TagItem, RepositoryError> { promise in
      DispatchQueue.main.asyncAfter(deadline: .now() + self.timeInterval , execute: {
        guard let index = self.tagItems.firstIndex(of: tag) else {
          promise(.failure(.entryNotFound))
          return
        }
        self.tagItems[index] = tag
        promise(.success(tag))
      })
    }.eraseToAnyPublisher()
  }
  
  func getAllTagsPublisher() -> TagsPublisher {
    return Future<TagsDictionary, RepositoryError> { promise in
      DispatchQueue.main.asyncAfter(deadline: .now() + self.timeInterval , execute: {
        promise(.success(self.mapToTagsDictionary(from: self.tagItems)))
      })
    }.eraseToAnyPublisher()
  }
  
  private func mapToTagsDictionary(from tags: [TagItem]) -> TagsDictionary {
    var tagsDictionary: TagsDictionary = [:]
    for tag in tags {
      tagsDictionary[tag.id] = tag
    }
    return tagsDictionary
  }
}
