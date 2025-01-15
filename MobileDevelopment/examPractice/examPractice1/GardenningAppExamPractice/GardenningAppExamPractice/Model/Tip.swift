//
//  Tip.swift
//  GardenningAppExamPractice
//
//  Created by Alex Campean on 2/4/23.
//

import Foundation
import RealmSwift

final class LocalStorageTip: Object, ObjectKeyIdentifiable {
    @Persisted(primaryKey: true) var id: Int
    @Persisted var name: String
    @Persisted var desc: String
    @Persisted var materials: String
    @Persisted var steps: String
    @Persisted var category: String
    @Persisted var difficulty: String
    
    convenience init(tip: TipDTO.Response) {
        self.init();
        self.id = tip.id;
        self.name = tip.name;
        self.desc = tip.description;
        self.materials = tip.materials;
        self.steps = tip.steps;
        self.category = tip.category;
        self.difficulty = tip.difficulty;
    }
}

enum TipDTO {
    struct Response: Decodable {
        var id: Int
        var name: String
        var description: String
        var materials: String
        var steps: String
        var category: String
        var difficulty: String
    }

    struct Request: Encodable {
        var name: String
        var description: String
        var materials: String
        var steps: String
        var category: String
        var difficulty: String
    }
}

struct Tip: Identifiable {
    var id: Int
    var name: String
    var description: String
    var materials: String
    var steps: String
    var category: String
    var difficulty: String
    
    init(tip: TipDTO.Response) {
        self.id = tip.id;
        self.name = tip.name;
        self.description = tip.description;
        self.materials = tip.materials;
        self.steps = tip.steps;
        self.category = tip.category;
        self.difficulty = tip.difficulty;
    }
    
    init(tip: LocalStorageTip) {
        self.id = tip.id;
        self.name = tip.name;
        self.description = tip.desc;
        self.materials = tip.materials;
        self.steps = tip.steps;
        self.category = tip.category;
        self.difficulty = tip.difficulty;
    }
    
    static func < (lhs: Tip, rhs: Tip) -> Bool {
        return lhs.difficulty < rhs.difficulty
    }
}
