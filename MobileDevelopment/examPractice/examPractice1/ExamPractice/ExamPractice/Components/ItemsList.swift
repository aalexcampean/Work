//
//  ItemsList.swift
//  ExamPractice
//
//  Created by Alex Campean on 2/4/23.
//

import SwiftUI

struct ItemsList: View {
    var items: [Tip];
    
    var body: some View {
        List(items) { item in
            ItemRow(item: item)
        }
    }
}

struct ItemsList_Previews: PreviewProvider {
    static var previews: some View {
        ItemsList(items: [Tip(i: TipDTO(id: 1, name: "Blossoming Brigade", description: "Provide proper light and air circulation for your plants.", materials: "Gardening Gloves", steps: "Mulch around the plants to retain moisture and suppress weeds.", category: "Planting", difficulty: "medium"))])
    }
}
