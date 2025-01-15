//
//  Categories.swift
//  ExamPractice
//
//  Created by Alex Campean on 2/4/23.
//

import Foundation
import RealmSwift

final class RealmCategory: Object, ObjectKeyIdentifiable {
    @Persisted(primaryKey: true) var _id: Int
    @Persisted var name: String
    
    convenience init(c: CategoryDTO, id: Int) {
        self.init();
        self._id = id
        self.name = c.name
    }
}

struct Category: Identifiable {
    var id: Int
    var name: String
    
    init(c: RealmCategory) {
        self.id = c._id
        self.name = c.name
    }
    
    init(c: CategoryDTO, id: Int) {
        self.id = id;
        self.name = c.name;
    }
    
}

struct CategoryDTO: Decodable {
    var name: String
}
