//
//  TipCreator.swift
//  ExamPractice
//
//  Created by Alex Campean on 2/4/23.
//

import SwiftUI

struct TipCreator: View {
    @EnvironmentObject var storage: AppMem;
    
    @State private var name: String = ""
    @State private var description: String = ""
    @State private var materials: String = ""
    @State private var steps: String = ""
    @State private var category: String = ""
    @State private var difficulty: String = ""
    
    @State private var showNetworkAlert = false;
    
    private func addProduct() {
        guard storage.connected else {
            showNetworkAlert = true
            return
        }
        
        Task {
            print("sending post request...")
            let url = URL(string: "http://localhost:2302/tip")!
            var request = URLRequest(url: url)
            request.httpMethod = "POST"
            request.setValue("application/json", forHTTPHeaderField: "Content-Type")
            request.httpBody = try? JSONSerialization.data(withJSONObject: [
                "name": name,
                "description": description,
                "materials": materials,
                "steps": steps,
                "category": category,
                "difficulty": difficulty,
            ])
            do {
                _ = try await URLSession.shared.data(for: request)
                storage.refresh()
            } catch {
                storage.errorOccurred.send("Failed adding new tip");
            }
            print("post request sent")
        }
    }
    
    var body: some View {
        TextField("Name", text: $name)
        TextField("Description", text: $description)
        TextField("Materials", text: $materials)
        TextField("Steps", text: $steps)
        TextField("Category", text: $category)
        TextField("Difficulty", text: $difficulty)
        Button(action: addProduct) {
            Text("Add")
        };
    }
}

struct TipCreator_Previews: PreviewProvider {
    static var previews: some View {
        TipCreator()
    }
}
