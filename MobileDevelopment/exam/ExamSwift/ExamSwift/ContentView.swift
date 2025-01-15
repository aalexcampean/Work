//
//  ContentView.swift
//  ExamSwift
//
//  Created by Alex Campean on 2/5/23.
//

import SwiftUI

struct ContentView: View {
    @StateObject var controller = Controller()
    @State var isAlertShown = false
    @State var errorMessage: String? = nil
    
    var body: some View {
        TabView {
            DatesView()
                .tabItem {
                    Label("Dates", systemImage: "list.dash")
                }
            TopFitnessProgressesView()
                .tabItem {
                    Label("Top3", systemImage: "list.dash")
                }
        }
        .environmentObject(controller)
        .onReceive(controller.errorOccurred) { error in
            self.errorMessage = error.toString()
            self.isAlertShown = true
        }
        .alert(self.errorMessage ?? "", isPresented: self.$isAlertShown) {
            Button("OK") {
                self.isAlertShown = false
                self.errorMessage = ""
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
