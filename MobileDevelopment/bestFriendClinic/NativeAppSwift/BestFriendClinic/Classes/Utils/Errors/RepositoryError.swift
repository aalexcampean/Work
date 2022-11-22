//
//  RepositoryError.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/14/22.
//

import Foundation

enum RepositoryError: Error {
    case internalFailure
    case noInternet
    case entryNotFound
    case serverError(String)
    
    func toString() -> String{
        switch self {
        case .internalFailure:
            return "There was an error while getting the list of appointments"
        case .noInternet:
            return "No Internet Connection"
        case .entryNotFound:
            return "Appointment Not Found"
        case .serverError(let serverError):
            return serverError
        }
    }
}
