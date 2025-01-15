//
//  Tip.swift
//  ExamPractice
//
//  Created by Alex Campean on 2/4/23.
//

import Foundation
import RealmSwift

final class RealmTip: Object, ObjectKeyIdentifiable {
    @Persisted(primaryKey: true) var _id: Int
    @Persisted var name: String
    @Persisted var desc: String
    @Persisted var materials: String
    @Persisted var steps: String
    @Persisted var category: String
    @Persisted var difficulty: String
    
    convenience init(i: TipDTO) {
        self.init();
        self._id = i.id;
        self.name = i.name;
        self.desc = i.description;
        self.materials = i.materials;
        self.steps = i.steps;
        self.category = i.category;
        self.difficulty = i.difficulty;
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
    
    init(i: TipDTO) {
        self.id = i.id;
        self.name = i.name;
        self.description = i.description;
        self.materials = i.materials;
        self.steps = i.steps;
        self.category = i.category;
        self.difficulty = i.difficulty;
    }
    
    init(i: RealmTip) {
        self.id = i._id;
        self.name = i.name;
        self.description = i.desc;
        self.materials = i.materials;
        self.steps = i.steps;
        self.category = i.category;
        self.difficulty = i.difficulty;
    }
}

struct TipDTO: Decodable {
    var id: Int
    var name: String
    var description: String
    var materials: String
    var steps: String
    var category: String
    var difficulty: String
}

