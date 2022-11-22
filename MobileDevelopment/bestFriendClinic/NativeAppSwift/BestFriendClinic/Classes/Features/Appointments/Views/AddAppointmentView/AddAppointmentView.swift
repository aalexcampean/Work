//
//  AddAppointmentView.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/12/22.
//

import SwiftUI

struct AddAppointmentView: View {
    @EnvironmentObject var dependecies: AppointmentsFeatureDependencies
    @StateObject var viewModel: AddAppointmentViewModel
    @Environment(\.presentationMode) private var presentationMode
    
    var body: some View {
        NavigationView {
            VStack (spacing: 10.0){
                Form {
                    Section(content: {
                        appointmentTypePicker
                        appointmentDatePicker
                        appointmentVetPicker
                        appointmentPetPicker
                    }, header: {
                        Text("Info")
                            .font(.caption)
                    })
                    
                    Section(content: {
                        appointmentLocationPicker
                    }, header: {
                        Text("Location")
                            .font(.caption)
                    })
                    
                    Section(content: {
                        VStack(alignment: .trailing, spacing: 8.0) {
                            textFieldView
                            textFieldCharacterCounterView
                        }
                        .padding(10.0)
                    }, header: {
                        Text("Description")
                            .font(.caption)
                    })
                    
                    Section(content: {
                        HStack{
                            Text("Amount to be paid")
                                .font(.caption.bold())
                                .foregroundColor(ColorsCatalog.secondaryText)
                            Spacer()
                            Text("\(viewModel.typeSelection.associatedPrice) RON")
                                .foregroundColor(ColorsCatalog.complementaryAccent)
                        }
                        
                    }, header: {
                        Text("Price")
                            .font(.caption)
                    })
                }
            }
            .accentColor(ColorsCatalog.complementaryAccent)
            .background(ColorsCatalog.appBackground)
            .navigationTitle(viewModel.addAppointmentTitle)
            .navigationBarTitleDisplayMode(.inline)
            .toolbar {
                ToolbarItemGroup(placement: .cancellationAction) {
                    Button {
                        presentationMode.wrappedValue.dismiss()
                    } label: {
                        Text("Cancel")
                    }
                }
                
                ToolbarItemGroup(placement: .confirmationAction) {
                    Button {
                        viewModel.addAppointment()
                        presentationMode.wrappedValue.dismiss()
                    } label: {
                        Text("Done")
                    }
                }
            }
        }
        .foregroundColor(ColorsCatalog.accent)
    }
    
    @ViewBuilder private var appointmentTypePicker: some View {
        Picker(selection: $viewModel.typeSelection) {
            ForEach(viewModel.typeOptions, id: \.self) { option in
                Text(option.rawValue)
                    .foregroundColor(ColorsCatalog.complementaryAccent)
            }
        } label: {
            Text("Type")
                .font(.caption.bold())
                .foregroundColor(ColorsCatalog.secondaryText)
        }
        .pickerStyle(.menu)
    }
    
    @ViewBuilder private var appointmentDatePicker: some View {
        DatePicker(selection: $viewModel.dateSelection, in: Date()...) {
            Text("Date")
                .font(.caption.bold())
                .foregroundColor(ColorsCatalog.secondaryText)
        }
    }
    
    @ViewBuilder private var appointmentVetPicker: some View {
        Picker(selection: $viewModel.vetSelection) {
            ForEach(viewModel.vetOptions, id: \.self) { option in
                Text(option)
                    .foregroundColor(ColorsCatalog.complementaryAccent)
            }
        } label: {
            Text("Vet")
                .font(.caption.bold())
                .foregroundColor(ColorsCatalog.secondaryText)
        }
        .pickerStyle(.menu)
    }
    
    @ViewBuilder private var appointmentPetPicker: some View {
        Picker(selection: $viewModel.petSelection) {
            ForEach(viewModel.petOptions, id: \.self) { option in
                Text(option)
                    .foregroundColor(ColorsCatalog.complementaryAccent)
            }
        } label: {
            Text("Pet")
                .font(.caption.bold())
                .foregroundColor(ColorsCatalog.secondaryText)
        }
        .pickerStyle(.menu)
    }
    
    @ViewBuilder private var appointmentLocationPicker: some View {
        Picker(selection: $viewModel.locationSelection) {
            ForEach(viewModel.locationOptions, id: \.self) { option in
                Text(option)
                    .foregroundColor(ColorsCatalog.complementaryAccent)
            }
        } label: {
            Text("Location")
                .font(.caption.bold())
                .foregroundColor(ColorsCatalog.secondaryText)
        }
        .pickerStyle(.segmented)
    }
    
    @ViewBuilder private var textFieldView: some View {
        TextEditor(text: $viewModel.inputDescription)
            .overlay(
                RoundedRectangle(cornerRadius: 12.0)
                    .stroke(viewModel.isTextFieldSelected ? ColorsCatalog.complementaryAccent : ColorsCatalog.secondaryText)
            )
            .frame(height: 100.0)
            .disabled(viewModel.inputDescription.count == 100 ? true : false)
            .onTapGesture {
                viewModel.selectTextField()
            }
    }
    
    @ViewBuilder private var textFieldCharacterCounterView: some View {
        Text("\(viewModel.inputDescription.count) / 100 characters")
            .font(.caption.bold())
            .foregroundColor(ColorsCatalog.secondaryText)
    }
}

struct AddAppointmentView_Previews: PreviewProvider {
    static var previews: some View {
        let state = AppointmetsState()
        let mockedRepository = MockedAppointmentsRepository(timeInterval: 0.3)
        let service = DefaultAppointmentsService(repository: mockedRepository, state: state)
        
        AddAppointmentView(viewModel: AddAppointmentViewModel(service: service, state: state))
    }
}
