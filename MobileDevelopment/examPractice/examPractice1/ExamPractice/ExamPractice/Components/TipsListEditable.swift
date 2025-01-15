//
//  TipsListEditable.swift
//  ExamPractice
//
//  Created by Alex Campean on 2/4/23.
//

import SwiftUI

struct TipsListEditable: View {
    @EnvironmentObject var storage: AppMem
    var items: [Tip];
    let mapNextDiff = [
        "easy": "medium",
        "medium": "hard",
        "hard": "easy",
    ]
    
    @State private var showNetworkAlert = false;
    @State private var refresh = false;
    
    func update() {
        refresh.toggle();
    }
    
    private func changeDiff(item: Tip) {
        guard storage.connected else {
            showNetworkAlert = true
            return
        }
        
        Task {
            print("sending post request...")
            print(item.id)
            let url = URL(string: "http://localhost:2302/difficulty")!
            var request = URLRequest(url: url)
            request.httpMethod = "POST"
            request.setValue("application/json", forHTTPHeaderField: "Content-Type")
            request.httpBody = try? JSONSerialization.data(withJSONObject: [
                "id": item.id,
                "difficulty": mapNextDiff[item.difficulty]!
            ])
            do {
                _ = try await URLSession.shared.data(for: request)
                storage.refresh()
                update();
            } catch {
                storage.errorOccurred.send("Failed adding new tip");
            }
            print("update request sent")
        }
    }
    
    var body: some View {
        List(items) { item in
            VStack {
                Text(item.name + " | " + item.difficulty).bold()
                Text(item.materials)
                Text(item.steps)
                Text(item.category)
                Button(action: {
                    changeDiff(item: item)
                }) {
                    Text("Change Difficulty")
                }
            }
        }
    }
}

