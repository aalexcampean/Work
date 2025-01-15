//
//  AddTipView.swift
//  GardenningAppExamPractice
//
//  Created by Alex Campean on 2/5/23.
//

import SwiftUI

struct AddTipView: View {
    @EnvironmentObject var controller: Controller;
    @Environment(\.presentationMode) private var presentationMode
    
    // MARK: - State properties
    @State var nameInput: String = ""
    @State var descriptionInput: String = ""
    @State var materialsInput: String = ""
    @State var stepsInput: String = ""
    @State var categoryInput: String = ""
    @State var difficultyInput : String = ""
    
    private func addTip() {
        guard controller.connected else {
            controller.errorOccurred.send(.noInternet)
            return
        }
        
        Task {
            print("sending post request...")
            guard let urlAddTip = URL(string: "http://localhost:2302/tip") else {
                controller.errorOccurred.send(.incorrectURL)
                return
            }
            
            var request = URLRequest(url: urlAddTip)
            request.httpMethod = "POST"
            request.setValue("application/json", forHTTPHeaderField: "Content-Type")
            request.httpBody = try! JSONEncoder().encode(TipDTO.Request(name: nameInput,
                                                                        description: descriptionInput,
                                                                        materials: materialsInput,
                                                                        steps: stepsInput,
                                                                        category: categoryInput,
                                                                        difficulty: difficultyInput))
            
            do {
                _ = try await URLSession.shared.data(for: request)
                controller.refresh()
            } catch {
                controller.errorOccurred.send(.addFailure);
            }
            print("post request sent")
        }
    }
    
    var body: some View {
        NavigationView {
            VStack (spacing: 10.0){
                Form {
                    TextField("Name", text: $nameInput)
                    TextField("Description", text: $descriptionInput)
                    TextField("Materials", text: $materialsInput)
                    TextField("Steps", text: $stepsInput)
                    TextField("Category", text: $categoryInput)
                    TextField("Difficulty", text: $difficultyInput)
                }
            }
            .navigationTitle("Add Tip")
            .navigationBarTitleDisplayMode(.inline)
            .toolbar {
                ToolbarItemGroup(placement: .cancellationAction) {
                    Button {
                        presentationMode.wrappedValue.dismiss()
                    } label: {
                        Text("Cancel")
                    }
                }
                
                ToolbarItemGroup(placement: .confirmationAction) {
                    Button {
                        addTip()
                        presentationMode.wrappedValue.dismiss()
                    } label: {
                        Text("Done")
                    }
                }
            }
        }
    }
}

struct AddTipView_Previews: PreviewProvider {
    static var previews: some View {
        AddTipView()
    }
}
