//
//  Date.swift
//  ExamSwift
//
//  Created by Alex Campean on 2/5/23.
//

import Foundation
import RealmSwift

class LocalStorageDate: Object, ObjectKeyIdentifiable {
    @Persisted(primaryKey: true) var id: Int
    @Persisted var date: String
    
    convenience init(id: Int, date: DateDTO) {
        self.init();
        self.id = id
        self.date = date.date
    }
}

struct DateDTO: Decodable {
    var date: String
}

struct Date: Identifiable {
    var id: Int
    var date: String
    
    init(date: LocalStorageDate) {
        self.id = date.id
        self.date = date.date
    }
    
    init(id: Int, date: DateDTO) {
        self.id = id;
        self.date = date.date
    }
}
