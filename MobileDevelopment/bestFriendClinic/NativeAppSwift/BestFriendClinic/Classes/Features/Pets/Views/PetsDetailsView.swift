//
//  PetsDetailsView.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/12/22.
//

import SwiftUI

struct PetsDetailsView: View {
    private let model: PetUIModel
    
    init (model: PetUIModel) {
        self.model = model
    }
    
    var body: some View {
        Text("This is the detail view for \(model.name)")
    }
}

struct PetsDetailsView_Previews: PreviewProvider {
    static var previews: some View {
        PetsDetailsView(model: PetUIModel(id: "1",
                                          name: "Abel",
                                          breed: "golden retriever",
                                          animal: "dog",
                                          age: 5))
    }
}
