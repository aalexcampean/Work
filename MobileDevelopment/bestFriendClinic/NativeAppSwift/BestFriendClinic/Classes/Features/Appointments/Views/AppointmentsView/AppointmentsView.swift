//
//  AppointmentsView.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/8/22.
//

import SwiftUI

struct AppointmentsView: View {
    @EnvironmentObject var dependecies: AppointmentsFeatureDependencies
    @StateObject var viewModel: AppointmentsViewModel
    @State var showAddAppointmentView = false
    
    var body: some View {
        NavigationView {
            VStack(alignment: .leading){
                listView(with: viewModel.presentationState.currentValue ?? [])
            }
            .background(ColorsCatalog.appBackground)
            .navigationTitle("Appointments")
            .toolbar {
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button(action: {
                        showAddAppointmentView.toggle()
                    }) {
                        Image(systemName: "plus")
                            .foregroundColor(ColorsCatalog.accent)
                    }
                    .sheet(isPresented: $showAddAppointmentView) {
                        AddAppointmentView(viewModel: AddAppointmentViewModel(service: dependecies.service, state: dependecies.state))
                    }
                }
            }
        }
    }
    
    private func listView(with sections: [AppointmentSectionUIModel]) -> some View {
        ScrollView{
            LazyVStack(alignment: .leading, spacing: 10.0){
                ForEach(sections) { section in
                    Section {
                        ForEach(section.items) { item in
                            NavigationLink(destination: AppointmentDetailView(viewModel: AppointmentDetailsViewModel(service: dependecies.service,
                                                                                                                     state: dependecies.state,
                                                                                                                     mapper: dependecies.mapper,
                                                                                                                     appointmentID: item.id)),
                                           label: {
                                AppointmentCardView(viewModel: AppointmentCardViewModel(appointment: item,
                                                                                        service: dependecies.service,
                                                                                        state: dependecies.state))
                            })
                        }
                    } header: {
                        Text(section.title)
                            .font(.caption)
                            .foregroundColor(ColorsCatalog.secondaryText)
                    }
                }
            }
            .padding(.horizontal, 16.0)
        }
    }
}

struct AppointmentsView_Previews: PreviewProvider {
    static var previews: some View {
        let state = AppointmetsState()
        let mockedRepository = MockedAppointmentsRepository(timeInterval: 0.3)
        let appointmentsMapper = DefaultAppointmentUIMapper()
        let service = DefaultAppointmentsService(repository: mockedRepository, state: state)
        let dependencies = AppointmentsFeatureDependencies(state: state, service: service, mapper: appointmentsMapper)
        
        AppointmentsView(viewModel: AppointmentsViewModel(service: dependencies.service,
                                                          state: dependencies.state,
                                                          mapper: dependencies.mapper))
    }
}
