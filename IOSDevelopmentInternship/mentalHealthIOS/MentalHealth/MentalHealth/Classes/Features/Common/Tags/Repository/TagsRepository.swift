//
//  TagsRepository.swift
//  MentalHealth
//
//  Created by alexcampean on 07.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation
import Combine

typealias TagPublisher = AnyPublisher<TagItem, RepositoryError>
typealias TagsPublisher = AnyPublisher<TagsDictionary, RepositoryError>

protocol TagsRepository {
  func add(tag: TagItem) -> TagPublisher
  func delete(tag: TagItem) -> TagPublisher
  func update(tag: TagItem) -> TagPublisher
  
  func getAllTagsPublisher() -> TagsPublisher
}
