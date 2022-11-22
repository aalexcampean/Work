//
//  ViewError.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/15/22.
//

import Foundation

enum ViewError: Error {
    case deleteItem
    case addUpdateItem
    
    func toString() -> String{
        switch self {
        case .deleteItem:
            return "Are you sure you want to delete this item?"
        case .addUpdateItem:
            return "Missing Appointment fields"
        }
    }
}
