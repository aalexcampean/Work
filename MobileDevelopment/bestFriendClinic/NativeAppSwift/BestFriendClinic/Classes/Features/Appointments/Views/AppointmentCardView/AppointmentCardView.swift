//
//  AppointmentCardView.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/8/22.
//

import SwiftUI

struct AppointmentCardView: View {
    @EnvironmentObject var dependecies: AppointmentsFeatureDependencies
    @StateObject var viewModel: AppointmentCardViewModel
    
    var body: some View {
        HStack(alignment: .center, spacing: 10.0){
            Image(viewModel.appointment.type.associatedImage)
                .padding(8.0)
                .background(
                    RoundedRectangle(cornerRadius: 12.0)
                        .fill(LinearGradient(
                            gradient: Gradient(colors: [ColorsCatalog.transparentAccent,
                                                        ColorsCatalog.complementaryAccent]),
                            startPoint: .bottomLeading,
                            endPoint: .topTrailing))
                        .shadow(color: ColorsCatalog.shadow, radius: 4.0, y: 2.0)
                )
            
            VStack(alignment: .leading, spacing: 4.0){
                Text(viewModel.appointment.type.rawValue)
                    .foregroundColor(ColorsCatalog.appointmentCardTitle)
                    .font(.title2.bold())
                
                Label(viewModel.appointment.date, systemImage: "calendar")
                    .font(.caption2)
                    .foregroundColor(ColorsCatalog.accent)
                
                Label(viewModel.appointment.petName, systemImage: "pawprint.fill")
                    .font(.caption2)
                    .foregroundColor(ColorsCatalog.accent)
            }
            
            Spacer()
        }
        .padding(10)
        .background(RoundedRectangle(cornerRadius: 12.0)
            .fill(ColorsCatalog.itemBackground)
            .shadow(color: ColorsCatalog.shadow.opacity(0.5), radius: 4.0, y: 2.0))
    }
}

struct AppointmentView_Previews: PreviewProvider {
    static var previews: some View {
        let appointment1 = AppointmentUIModel(id: "1",
                                                     type: AppointmentType(rawValue: "Ears Cleaning")!,
                                                     date: "Nov 12, 2:00 PM",
                                                     location: "Str. Universitatii 17",
                                                     petName: "Ludmila",
                                                     vetName: "Claudiu Pop")
        
        let state = AppointmetsState()
        let mockedRepository = MockedAppointmentsRepository(timeInterval: 0.3)
        let appointmentsMapper = DefaultAppointmentUIMapper()
        let service = DefaultAppointmentsService(repository: mockedRepository, state: state)
        let dependencies = AppointmentsFeatureDependencies(state: state, service: service, mapper: appointmentsMapper)
        
        AppointmentCardView(viewModel: AppointmentCardViewModel(appointment: appointment1, service: service, state: state))
    }
}
