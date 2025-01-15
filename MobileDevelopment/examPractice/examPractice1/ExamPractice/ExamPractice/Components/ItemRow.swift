//
//  ItemRow.swift
//  ExamPractice
//
//  Created by Alex Campean on 2/4/23.
//

import SwiftUI

struct ItemRow: View {
    @EnvironmentObject var storage: AppMem;
    var item: Tip;
    @State var showNetworkAlert = false
    
    private func delete() {
        guard storage.connected else {
            showNetworkAlert = true;
            return;
        }
        
        Task {
            print("Sending delete request")
            
            var request = URLRequest(url: URL(string: "http://localhost:2302/tip/\(item.id)")!)
            request.httpMethod = "DELETE"
            do {
                _ = try await URLSession.shared.data(for: request)
                storage.refresh()
            } catch {
                storage.errorOccurred.send("Could not send delete request");
            }
        }
        
    }
    
    var body: some View {
        HStack{
            VStack {
                Text(item.name + "|" + item.category).bold()
                Divider()
                Text(item.description)
                Divider()
                Text(item.steps)
                Divider()
                Text(item.difficulty)
                Divider()
                Text(item.materials)
            }.padding()
            Button (action: {
                delete();
            }) {
                Image(systemName: "trash").font(.system(size: 30))
            }.frame(alignment: .trailing)
        }
    }
}

struct ItemRow_Previews: PreviewProvider {
    static var previews: some View {
        ItemRow(item: Tip(i: TipDTO(id: 1, name: "Blossoming Brigade", description: "Provide proper light and air circulation for your plants.", materials: "Gardening Gloves", steps: "Mulch around the plants to retain moisture and suppress weeds.", category: "Planting", difficulty: "medium")))
    }
}
