//
//  CategoriesView.swift
//  ExamPractice
//
//  Created by Alex Campean on 2/4/23.
//

import SwiftUI

struct CategoriesView: View {
    
    var body: some View {
        VStack {
            CategoryList()
            Divider()
            TipCreator()
        }
    }
    
}
