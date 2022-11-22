//
//  PetCardView.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/10/22.
//

import SwiftUI

struct PetCardView: View {
    private let model: PetUIModel
    
    init (model: PetUIModel) {
        self.model = model
    }
    
    var body: some View {
        ZStack {
            RoundedRectangle(cornerRadius: 12.0)
                .fill(LinearGradient(
                    gradient: Gradient(colors: [ColorsCatalog.transparentAccent,
                                                ColorsCatalog.complementaryAccent]),
                    startPoint: .bottomLeading,
                    endPoint: .topTrailing))
                .offset(x: 10.0, y: -10.0)
            
            RoundedRectangle(cornerRadius: 12.0)
                .fill(.ultraThinMaterial)
            
            HStack{
                VStack(alignment: .leading, spacing: 8.0) {
                    Text(model.name)
                        .foregroundColor(ColorsCatalog.petCardTitle)
                        .font(.title2.bold())
                        .lineLimit(1)
                    
                    Label("\(model.age) years old", systemImage: "person.text.rectangle")
                        .foregroundColor(ColorsCatalog.accent)
                        .font(.caption2)
                        .lineLimit(1)
                    
                    Label(model.animal, systemImage: "pawprint.fill")
                        .foregroundColor(ColorsCatalog.accent)
                        .font(.caption2)
                        .lineLimit(1)
                    
                    Label(model.breed, systemImage: "circlebadge.fill")
                        .foregroundColor(ColorsCatalog.accent)
                        .font(.caption2)
                        .lineLimit(1)
                }
                
                Spacer()
            }
            .frame(height: 100.0)
            .frame(maxWidth: .infinity)
            .padding(.leading, 10)
            .background(ColorsCatalog.appBackground.opacity(0.15), in: RoundedRectangle(cornerRadius: 12.0))
        }
    }
}

struct PetCardView_Previews: PreviewProvider {
    static var previews: some View {
        let cards = [
            PetUIModel(id: "1",
                       name: "Abel",
                       breed: "golden retriever",
                       animal: "dog",
                       age: 5),
            PetUIModel(id: "2",
                       name: "Abel",
                       breed: "golden retriever",
                       animal: "dog",
                       age: 5),
            PetUIModel(id: "3",
                       name: "Abel",
                       breed: "golden retriever",
                       animal: "dog",
                       age: 5)
        ]
        
        let columns = [GridItem(.flexible(), spacing: 20.0), GridItem(.flexible())]
        
        ScrollView {
            LazyVGrid(columns: columns, spacing: 20.0) {
                ForEach(cards) { item in
                    PetCardView(model: item)
                }
                AddPetCardView()
            }
            .padding(.leading, 16)
            .padding(.trailing, 26)
        }
    }
}
