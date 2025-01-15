//
//  FitnessProgress.swift
//  ExamSwift
//
//  Created by Alex Campean on 2/5/23.
//

import Foundation
import RealmSwift

final class LocalStorageFitnessProgress: Object, ObjectKeyIdentifiable {
    @Persisted(primaryKey: true) var id: Int
    @Persisted var date: String
    @Persisted var type: String
    @Persisted var duration: Int
    @Persisted var distance: Int
    @Persisted var calories: Int
    @Persisted var rate: Int
    
    convenience init(fitnessProgress: FitnessProgressDTO.Response) {
        self.init();
        self.id = fitnessProgress.id
        self.date = fitnessProgress.date
        self.type = fitnessProgress.type
        self.duration = fitnessProgress.duration
        self.distance = fitnessProgress.distance
        self.calories = fitnessProgress.calories
        self.rate = fitnessProgress.rate
    }
}

enum FitnessProgressDTO {
    struct Response: Decodable {
        var id: Int
        var date: String
        var type: String
        var duration: Int
        var distance: Int
        var calories: Int
        var rate: Int
    }

    struct Request: Encodable {
        var date: String
        var type: String
        var duration: Int
        var distance: Int
        var calories: Int
        var rate: Int
    }
}

struct FitnessProgress: Identifiable {
    var id: Int
    var date: String
    var type: String
    var duration: Int
    var distance: Int
    var calories: Int
    var rate: Int
    
    init(fitnessProgress: FitnessProgressDTO.Response) {
        self.id = fitnessProgress.id;
        self.date = fitnessProgress.date
        self.type = fitnessProgress.type
        self.duration = fitnessProgress.duration
        self.distance = fitnessProgress.distance
        self.calories = fitnessProgress.calories
        self.rate = fitnessProgress.rate
    }
    
    init(fitnessProgress: LocalStorageFitnessProgress) {
        self.id = fitnessProgress.id;
        self.date = fitnessProgress.date
        self.type = fitnessProgress.type
        self.duration = fitnessProgress.duration
        self.distance = fitnessProgress.distance
        self.calories = fitnessProgress.calories
        self.rate = fitnessProgress.rate
    }
    
    static func > (lhs: FitnessProgress, rhs: FitnessProgress) -> Bool {
        return lhs.distance > rhs.distance
    }
}
