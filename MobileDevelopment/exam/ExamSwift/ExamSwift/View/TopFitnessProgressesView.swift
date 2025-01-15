//
//  TopFitnessProgressesView.swift
//  ExamSwift
//
//  Created by Alex Campean on 2/5/23.
//

import SwiftUI

struct TopFitnessProgressesView: View {
    @EnvironmentObject var controller: Controller
    
    var body: some View {
        NavigationView {
            ListView()
                .navigationTitle("Top 3 by distance")
        }
    }
    
    @ViewBuilder private func ListView() -> some View {
        List {
            ForEach(Array(controller.topFitnessProgresses.sorted(by: >).prefix(3))) { fitnessProgress in
                FitnessProgressView(fitnessProgress: fitnessProgress)
            }
        }
        .listStyle(.sidebar)
        .accentColor(Color.orange)
    }
    
    @ViewBuilder private func FitnessProgressView(fitnessProgress: FitnessProgress) -> some View {
        HStack(alignment: .center) {
            VStack (alignment: .leading) {
                Text(fitnessProgress.type)
                    .font(.title3.bold())
                    .foregroundColor(Color.orange)
                
                Text("\(fitnessProgress.date)")
                    .font(.caption)
                    .foregroundColor(Color.gray)
                
                Text("\(fitnessProgress.duration) minutes")
                    .font(.caption)
                    .foregroundColor(Color.gray)
                
                Text("\(fitnessProgress.distance) m")
                    .font(.caption)
                    .foregroundColor(Color.gray)
                
                Text("\(fitnessProgress.calories) calories burned")
                    .font(.caption)
                    .foregroundColor(Color.gray)
            }
            
            Spacer()
        }
    }
}

struct TopFitnessProgressesView_Previews: PreviewProvider {
    static var previews: some View {
        TopFitnessProgressesView()
    }
}
