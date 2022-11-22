//
//  RepositoryError.swift
//  MentalHealth
//
//  Created by alexcampean on 04.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

enum RepositoryError: Error {
  case internalFailure
  case noInternet
  case entryNotFound
  case serverError(String)
}
