//
//  CategoriesView.swift
//  GardenningAppExamPractice
//
//  Created by Alex Campean on 2/5/23.
//

import SwiftUI

struct CategoriesView: View {
    @EnvironmentObject var controller: Controller;
    @State var showAddTipView = false
    
    private func deleteTip(tip: Tip) {
        guard controller.connected else {
            controller.errorOccurred.send(.noInternet)
            return
        }
        
        Task {
            print("Sending delete request")
            guard let urlDeleteTip = URL(string: "http://localhost:2302/tip/\(tip.id)") else {
                controller.errorOccurred.send(.incorrectURL)
                return
            }
            
            var request = URLRequest(url: urlDeleteTip)
            request.httpMethod = "DELETE"
            
            do {
                _ = try await URLSession.shared.data(for: request)
                controller.refresh()
            } catch {
                controller.errorOccurred.send(.deleteFailure);
            }
            print("post request sent")
        }
    }
    
    var body: some View {
        NavigationView {
            ListView()
                .navigationTitle("Categories")
                .toolbar {
                    ToolbarItem(placement: .navigationBarTrailing) {
                        Button(action: {
                            showAddTipView.toggle()
                        }) {
                            Image(systemName: "plus")
                                .foregroundColor(Color.green)
                        }
                        .sheet(isPresented: $showAddTipView) {
                            AddTipView()
                        }
                    }
                }
        }
    }
    
    @ViewBuilder private func ListView() -> some View {
        List {
            ForEach(controller.categories) { category in
                Section {
                    ForEach(controller.tips.filter({$0.category == category.name})) { tip in
                        TipView(tip: tip)
                    }
                    .listRowSeparator(.hidden)
                } header: {
                    Text(category.name)
                        .font(.caption)
                        .foregroundColor(Color.gray)
                }
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
                
                Text(tip.difficulty)
                    .font(.caption)
            }
            
            Spacer()
            
            Button (action: {
                deleteTip(tip: tip);
            }) {
                Image(systemName: "trash")
                    .font(.caption)
                    .foregroundColor(Color.gray)
            }
        }
    }
}

struct CategoriesView_Previews: PreviewProvider {
    static var previews: some View {
        CategoriesView()
    }
}
