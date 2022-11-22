//
//  LoadingState.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 01.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation


/// Type representing the loading state of a generic value.
/// - Requires specialization with the value type and failure type.
enum LoadingState<Value, Failure: Error> {
  
  /// The loading is in progress.
  /// - The associated value contains the current value, if any.
  case loading(currentValue: Value? = nil)
  
  /// The loading was successful.
  ///- The associated value contains the new value, if any.
  case loaded(newValue: Value?)
  
  /// The loading failed.
  /// - The associated value contains the failure reason and the current value, if any.
  case failed(Failure, currentValue: Value? = nil)
  
  /// Represents the current value, if any.
  var currentValue: Value? {
    switch self {
    case .loading(currentValue: let currentValue):
      return currentValue
    case .loaded(newValue: let newValue):
      return newValue
    case .failed(_, currentValue: let currentValue):
      return currentValue
    }
  }
  
  /// Indicates if the state is `.loading`.
  var isLoading: Bool {
    switch self {
    case .loading:
      return true
    default:
      return false
    }
  }
  
  /// Indicates if the state is `.failed`.
  var isFailed: Bool {
    switch self {
    case .failed:
      return true
    default:
      return false
    }
  }
}


extension LoadingState where Failure: LocalizedError {
  
  /// Represents the failure reason, if the state is `.failed`.
  var failureReason: Failure? {
    switch self {
    case .failed(let error, _):
      return error
    default:
      return nil
    }
  }
}
