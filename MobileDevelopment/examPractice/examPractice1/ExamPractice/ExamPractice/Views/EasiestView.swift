//
//  EasiestView.swift
//  ExamPractice
//
//  Created by Alex Campean on 2/4/23.
//

import SwiftUI

struct EasiestView: View {
    @EnvironmentObject var storage: AppMem
    
    let diffMap: [String: Int] = [
        "easy": 1,
        "medium": 2,
        "hard": 3
    ]
    
    var body: some View {
        VStack {
            TipsListEditable(items: Array(storage.easiestTips.sorted(by: {$0.category < $1.category}).sorted { (lhs, rhs) in
                return diffMap[lhs.difficulty]! <= diffMap[rhs.difficulty]!
            }[0..<10]))
        }
    }
    
}
