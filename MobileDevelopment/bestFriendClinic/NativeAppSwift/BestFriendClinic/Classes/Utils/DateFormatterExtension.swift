//
//  DateFormatterExtension.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/13/22.
//

import Foundation

extension DateFormatter {
    static let dateTimeDTOFormatter: DateFormatter = {
        let formatter = DateFormatter()
        formatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ss'Z"
        return formatter
    }()
    
    static let dateTimeFormatter: DateFormatter = {
        let formatter = DateFormatter()
        formatter.dateFormat = "MMM dd yyyy, h:mm a"
        return formatter
    }()
}
