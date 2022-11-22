//
//  AppointmentDetailView.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/12/22.
//

import SwiftUI

struct AppointmentDetailView: View {
    @EnvironmentObject var dependecies: AppointmentsFeatureDependencies
    @StateObject var viewModel: AppointmentDetailsViewModel
    
    var body: some View {
        detailsCard(with: viewModel.presentationState.currentValue)
            .padding(16.0)
            .background(ColorsCatalog.appBackground)
            .navigationBarTitleDisplayMode(.inline)
            .toolbar {
                ToolbarItemGroup(placement: .navigationBarTrailing) {
                    Button(action: {
                        viewModel.showDeleteAppointmentAlert()
                    }) {
                        Image(systemName: "trash")
                            .foregroundColor(ColorsCatalog.accent)
                    }
                    .alert("Delete Appointment", isPresented: $viewModel.isDeleteAppointmentAlertShown) {
                        Button("No", role: .cancel) {
                            
                        }
                        Button("Yes", role: .destructive) {
                            viewModel.deleteAppointment()
                        }
                    } message: {
                        Text("Are you sure you want to delete this appointment?")
                    }
                    
                    Button(action: {
                        viewModel.showUpdateAppointmentView()
                    }) {
                        Image(systemName: "pencil")
                            .foregroundColor(ColorsCatalog.accent)
                    }
                    .sheet(isPresented: $viewModel.isUpdateAppointmentViewShown) {
                        EditAppointmentView(viewModel: viewModel)
                    }
                }
            }
    }
    
    private func detailsCard(with appointment: AppointmentUIModel?) -> some View {
        return VStack(spacing: 25.0) {
            if let appointment = appointment {
                VStack {
                    Image(appointment.type.associatedImage)
                        .resizable()
                        .scaledToFit()
                        .padding(10.0)
                        .frame(minWidth: 50.0, maxWidth: 200)
                        .background(
                            RoundedRectangle(cornerRadius: 12.0)
                                .fill(LinearGradient(
                                    gradient: Gradient(colors: [ColorsCatalog.transparentAccent,
                                                                ColorsCatalog.complementaryAccent]),
                                    startPoint: .bottomLeading,
                                    endPoint: .topTrailing))
                                .shadow(color: ColorsCatalog.shadow, radius: 4.0, y: 2.0)
                        )
                    
                    Text(appointment.type.rawValue)
                        .font(.title.bold())
                    
                    Text(appointment.date)
                        .font(.subheadline)
                        .foregroundColor(ColorsCatalog.complementaryAccent)
                }
                
                VStack(alignment: .leading, spacing: 36.0) {
                    HStack {
                        VStack(alignment: .leading, spacing: 16.0){
                            customLabel(text: appointment.location, iconName: "location")
                            customLabel(text: appointment.vetName, iconName: "person")
                            customLabel(text: appointment.petName, iconName: "pawprint.fill")
                        }
                        
                        Spacer()
                    }
                    
                    VStack(alignment: .leading, spacing: 8.0) {
                        Text("Details")
                            .bold()
                            .foregroundColor(ColorsCatalog.complementaryAccent)
                        Text(appointment.description ?? "")
                    }
                }
                .padding(10.0)
                .background(
                    RoundedRectangle(cornerRadius: 12.0)
                        .fill(ColorsCatalog.itemBackground)
                        .shadow(color: ColorsCatalog.shadow.opacity(0.5), radius: 4.0, y: 2.0)
                )
                
                HStack {
                    Text("Amount Due")
                        .font(.footnote.bold())
                        .foregroundColor(ColorsCatalog.secondaryText)
                    Spacer()
                    Text("\(appointment.type.associatedPrice) RON")
                        .font(.footnote.bold())
                }
                .padding(10)
                
                Spacer()
            }
        }
    }
    
    private func customLabel(text: String, iconName: String) -> some View {
        HStack {
            Image(systemName: iconName)
                .foregroundColor(ColorsCatalog.complementaryAccent)
            
            Text(text)
        }
    }
    
}

struct AppointmentDetailsView_Previews: PreviewProvider {
    static var previews: some View {
        let state = AppointmetsState()
        let mockedRepository = MockedAppointmentsRepository(timeInterval: 0.3)
        let appointmentsMapper = DefaultAppointmentUIMapper()
        let service = DefaultAppointmentsService(repository: mockedRepository, state: state)
        
        AppointmentDetailView(viewModel: AppointmentDetailsViewModel(service: service,
                                                                     state: state,
                                                                     mapper: appointmentsMapper,
                                                                     appointmentID: "1"))
    }
}
