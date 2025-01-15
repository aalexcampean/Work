//
//  ContentView.swift
//  ExamPractice
//
//  Created by Alex Campean on 2/4/23.
//

import SwiftUI

struct ContentView: View {
    @StateObject var storage = AppMem()
    
    @State var isAlertShown = false
    @State var errorMessage: String? = nil
    
    var body: some View {
        TabView {
            CategoriesView()
                .tabItem {
                    Label("Main", systemImage: "list.dash")
                }
            EasiestView()
                .tabItem {
                    Label("Difficulty", systemImage: "list.dash")
                }
            
        }
        .environmentObject(storage)
        .onReceive(storage.errorOccurred) { error in
            self.errorMessage = error.errorDescription
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
