//
//  DatesView.swift
//  ExamSwift
//
//  Created by Alex Campean on 2/5/23.
//

import SwiftUI

struct DatesView: View {
    @EnvironmentObject var controller: Controller;
    @State var showAddTipView = false
    
    private func deleteFitnessProgress(fitnessProgress: FitnessProgress) {
        guard controller.connected else {
            controller.errorOccurred.send(.noInternet)
            return
        }
        
        Task {
            print("---------- Sending delete request")
            guard let urlDeleteFitnessProgress = URL(string: "http://localhost:2305/entry/\(fitnessProgress.id)") else {
                controller.errorOccurred.send(.incorrectURL)
                return
            }
            
            var request = URLRequest(url: urlDeleteFitnessProgress)
            request.httpMethod = "DELETE"
            
            do {
                _ = try await URLSession.shared.data(for: request)
                controller.refresh()
            } catch {
                controller.errorOccurred.send(.deleteFailure);
            }
            print("---------- Delete request sent")
        }
    }
    
    var body: some View {
        NavigationView {
            ListView()
                .disabled(controller.isPending)
                .overlay {
                    if controller.isPending {
                        ProgressView()
                            .frame(maxWidth: .infinity,
                                   maxHeight: .infinity)
                            .background(Color.white)
                    }
                }
                .navigationTitle("Dates")
                .toolbar {
                    ToolbarItem(placement: .navigationBarTrailing) {
                        Button(action: {
                            showAddTipView.toggle()
                        }) {
                            Image(systemName: "plus")
                                .foregroundColor(Color.green)
                        }
                        .sheet(isPresented: $showAddTipView) {
                            AddFitnessProgressView()
                        }
                    }
                }
        }
    }
    
    @ViewBuilder private func ListView() -> some View {
        List {
            ForEach(controller.dates) { date in
                Section {
                    ForEach(controller.fitnesProgresses.filter({$0.date == date.date})) { fitnessProgress in
                        FitnessProgressView(fitnessProgress: fitnessProgress)
                    }
                    .listRowSeparator(.hidden)
                } header: {
                    Text(date.date)
                        .font(.caption)
                        .foregroundColor(Color.gray)
                }
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
            
            Button (action: {
                deleteFitnessProgress(fitnessProgress: fitnessProgress);
            }) {
                Image(systemName: "trash")
                    .font(.caption)
                    .foregroundColor(Color.gray)
            }
        }
    }
}

struct DatesView_Previews: PreviewProvider {
    static var previews: some View {
        DatesView()
    }
}
