//
//  MainLandingView.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/8/22.
//

import SwiftUI

struct MainLandingView: View {
    // MARK: - Dependencies
    @EnvironmentObject var appointmentsDependencies: AppointmentsFeatureDependencies
    
    // MARK: - Constants
    let appointmentsTabTitle = "Appointments"
    let petsTabTitle = "Pets"
    
    var body: some View {
        TabView {
            AppointmentsView(viewModel: AppointmentsViewModel(service: appointmentsDependencies.service,
                                                              state: appointmentsDependencies.state,
                                                              mapper: appointmentsDependencies.mapper))
            .tabItem {
                Label(appointmentsTabTitle, systemImage: "calendar")
            }
            
            PetsView()
                .tabItem {
                    Label(petsTabTitle, systemImage: "pawprint.fill")
                }
        }
        .accentColor(ColorsCatalog.accent)
    }
}

struct MainLandingView_Previews: PreviewProvider {
    static var previews: some View {
        MainLandingView()
    }
}
