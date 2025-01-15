//
//  AddFitnessProgressView.swift
//  ExamSwift
//
//  Created by Alex Campean on 2/5/23.
//

import SwiftUI

struct AddFitnessProgressView: View {
    @EnvironmentObject var controller: Controller;
    @Environment(\.presentationMode) private var presentationMode
    
    // MARK: - State properties
    @State var dateInput: String = ""
    @State var typeInput: String = ""
    @State var durationInput: String = ""
    @State var distanceInput: String = ""
    @State var caloriesInput: String = ""
    @State var rateInput : String = ""
    
    private func addFitnessProgress() {
        guard controller.connected else {
            controller.errorOccurred.send(.noInternet)
            return
        }
        
        Task {
            print("---------- Sending post request")
            guard let urlAddTip = URL(string: "http://localhost:2305/entry") else {
                controller.errorOccurred.send(.incorrectURL)
                return
            }
            
            var request = URLRequest(url: urlAddTip)
            request.httpMethod = "POST"
            request.setValue("application/json", forHTTPHeaderField: "Content-Type")
            request.httpBody = try! JSONEncoder().encode(FitnessProgressDTO.Request(date: dateInput,
                                                                                    type: typeInput,
                                                                                    duration: Int(durationInput) ?? 0  ,
                                                                                    distance: Int(distanceInput) ?? 0  ,
                                                                                    calories: Int(caloriesInput) ?? 0  ,
                                                                                    rate: Int(rateInput) ?? 0  ))
            
            do {
                _ = try await URLSession.shared.data(for: request)
                controller.refresh()
            } catch {
                controller.errorOccurred.send(.addFailure);
            }
            print("---------- Post request sent")
        }
    }
    
    var body: some View {
        NavigationView {
            VStack (spacing: 10.0){
                Form {
                    TextField("Date (yyyy-mm-dd)", text: $dateInput)
                    TextField("Type", text: $typeInput)
                    TextField("Duration", text: $durationInput)
                    TextField("Distance", text: $distanceInput)
                    TextField("Calories", text: $caloriesInput)
                    TextField("Rate", text: $rateInput)
                }
            }
            .navigationTitle("Add Fitness Progress")
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
                        addFitnessProgress()
                        presentationMode.wrappedValue.dismiss()
                    } label: {
                        Text("Done")
                    }
                }
            }
        }
    }
}

struct AddFitnessProgressView_Previews: PreviewProvider {
    static var previews: some View {
        AddFitnessProgressView()
    }
}
