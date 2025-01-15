//
//  CategoryList.swift
//  ExamPractice
//
//  Created by Alex Campean on 2/4/23.
//

import SwiftUI

struct CategoryList: View {
    @EnvironmentObject var storage: AppMem;
    
    var body: some View {
        NavigationView {
            List(storage.categories) { category in
                NavigationLink {
                    ItemsList(items: storage.tips.filter({$0.category == category.name}))
                } label: {
                    Text(category.name)
                }
            }
        }.navigationTitle("Categories")
    }
}

struct CategoryList_Previews: PreviewProvider {
    static var previews: some View {
        CategoryList()
    }
}
