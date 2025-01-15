//
//  ControllerError.swift
//  ExamSwift
//
//  Created by Alex Campean on 2/5/23.
//

import Foundation

enum ControllerError: Error {
    case internalFailure
    case noInternet
    case backOnline
    case incorrectURL
    case addFailure
    case deleteFailure
    case controllerError(String)
    
    func toString() -> String{
        switch self {
        case .internalFailure:
            return "There was an error while getting the list of fitness progresses"
        case .noInternet:
            return "No Internet Connection, limited functionalities available"
        case .backOnline:
            return "Back Online, refresing app"
        case .incorrectURL:
            return "The provided URL is incorrect"
        case .addFailure:
            return "Tip addition failed"
        case .deleteFailure:
            return "Tip deletion failed"
        case .controllerError(let controllerError):
            return controllerError
        }
    }
}
