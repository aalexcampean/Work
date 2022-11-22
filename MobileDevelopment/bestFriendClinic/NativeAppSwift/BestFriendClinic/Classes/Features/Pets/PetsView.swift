//
//  PetsView.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/8/22.
//

import SwiftUI

struct PetsView: View {
    @State private var viewModel = [
        PetUIModel(id: "1",
                   name: "Abel",
                   breed: "golden retriever",
                   animal: "dog",
                   age: 5),
        PetUIModel(id: "2",
                   name: "Ludmila",
                   breed: "persian",
                   animal: "cat",
                   age: 2),
        PetUIModel(id: "3",
                   name: "Snowflake",
                   breed: "chnchilla",
                   animal: "white",
                   age: 1)
    ]
    
    let columns = [GridItem(.flexible(), spacing: 20.0), GridItem(.flexible())]
    
    var body: some View {
        NavigationView {
            gridView()
                .background(ColorsCatalog.appBackground)
                .navigationTitle("My pets")
                .toolbar {
                    ToolbarItem(placement: .navigationBarTrailing) {
                        Button(action: {
                        }) {
                            Image(systemName: "person.crop.circle.fill")
                                .foregroundColor(ColorsCatalog.accent)
                        }
                    }
                }
        }
    }
    
    private func gridView() -> some View {
        return ScrollView {
            LazyVGrid(columns: columns, spacing: 20.0) {
                ForEach(viewModel) { petModel in
                    NavigationLink(destination: PetsDetailsView(model: petModel)) {
                        PetCardView(model: petModel)
                    }
                }
                AddPetCardView()
            }
            .padding(.leading, 16.0)
            .padding(.trailing, 26.0)
            .padding(.vertical, 16.0)
        }
    }
}

struct PetsView_Previews: PreviewProvider {
    static var previews: some View {
        PetsView()
    }
}
