//
//  AddPetCardView.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/11/22.
//

import SwiftUI

struct AddPetCardView: View {
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
                Spacer()
                
                Button {
                    print("Button Pressed!")
                } label: {
                    Image(systemName: "plus")
                        .frame(width: 60.0, height: 60.0)
                        .foregroundColor(ColorsCatalog.itemBackground)
                        .background(ColorsCatalog.accent.opacity(0.5), in: Circle())
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

struct AddPetCardView_Previews: PreviewProvider {
    static var previews: some View {
        let columns = [GridItem(.flexible(), spacing: 20.0), GridItem(.flexible())]
        
        ScrollView {
            LazyVGrid(columns: columns, spacing: 20.0) {
                
                AddPetCardView()
                AddPetCardView()
                AddPetCardView()
                AddPetCardView()
                
            }
            .padding(.leading, 16)
            .padding(.trailing, 26)
        }
    }
}
