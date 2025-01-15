//
//  Errors.swift
//  ExamPractice
//
//  Created by Alex Campean on 2/4/23.
//

import Foundation

extension String: LocalizedError {
    public var errorDescription: String? { self }
}
