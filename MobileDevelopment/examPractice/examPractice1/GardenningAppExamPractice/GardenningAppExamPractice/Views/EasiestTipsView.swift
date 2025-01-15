//
//  EasiestTipsView.swift
//  GardenningAppExamPractice
//
//  Created by Alex Campean on 2/5/23.
//

import SwiftUI

struct EasiestTipsView: View {
    @EnvironmentObject var controller: Controller
    @State private var showNetworkAlert = false
    
    let mapNextDiff = [
        "easy": "medium",
        "medium": "hard",
        "hard": "easy",
    ]
    
    private func changeDifficulty(tip: Tip) {
        guard controller.connected else {
            controller.errorOccurred.send(.noInternet)
            return
        }
        
        Task {
            print("sending post request...")
            print(tip.id)
            
            guard let urlChangeDifficulty = URL(string: "http://localhost:2302/difficulty") else {
                controller.errorOccurred.send(.incorrectURL)
                return
            }
            
            var request = URLRequest(url: urlChangeDifficulty)
            request.httpMethod = "POST"
            request.setValue("application/json", forHTTPHeaderField: "Content-Type")
            request.httpBody = try? JSONSerialization.data(withJSONObject: [
                "id": tip.id,
                "difficulty": mapNextDiff[tip.difficulty]!
            ])
            
            do {
                _ = try await URLSession.shared.data(for: request)
                controller.refresh()
            } catch {
                controller.errorOccurred.send(.addFailure);
            }
            print("update request sent")
        }
    }
    
    var body: some View {
        NavigationView {
            ListView()
                .navigationTitle("Easiest Tips")
        }
    }
    
    @ViewBuilder private func ListView() -> some View {
        List {
            ForEach(Array(controller.easiestTips.sorted(by: <).sorted(by: {$0.category < $1.category}).prefix(10))) { tip in
                TipView(tip: tip)
            }
        }
        .listStyle(.sidebar)
        .accentColor(Color.green)
    }
    
    @ViewBuilder private func TipView(tip: Tip) -> some View {
        HStack(alignment: .center) {
            VStack (alignment: .leading) {
                Text(tip.name)
                    .font(.title3.bold())
                    .foregroundColor(Color.green)
                
                Text(tip.description)
                    .font(.caption)
                    .lineLimit(1)
                
                Spacer()
                
                Text(tip.category)
                    .font(.caption)
                
                Text(tip.difficulty)
                    .font(.caption)
            }
            
            Spacer()
            
            Button (action: {
                changeDifficulty(tip: tip);
            }) {
                Text("Change Difficulty")
                    .font(.caption)
                    .foregroundColor(Color.gray)
            }
        }
    }
}

struct EasiestTipsView_Previews: PreviewProvider {
    static var previews: some View {
        EasiestTipsView()
    }
}
