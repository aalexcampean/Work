//
//  Category.swift
//  GardenningAppExamPractice
//
//  Created by Alex Campean on 2/4/23.
//

import Foundation
import RealmSwift

class LocalStorageCategory: Object, ObjectKeyIdentifiable {
    @Persisted(primaryKey: true) var id: Int
    @Persisted var name: String
    
    convenience init(id: Int, category: CategoryDTO) {
        self.init();
        self.id = id
        self.name = category.name
    }
}

struct CategoryDTO: Decodable {
    var name: String
}

struct Category: Identifiable {
    var id: Int
    var name: String
    
    init(category: LocalStorageCategory) {
        self.id = category.id
        self.name = category.name
    }
    
    init(id: Int, category: CategoryDTO) {
        self.id = id;
        self.name = category.name;
    }
}
