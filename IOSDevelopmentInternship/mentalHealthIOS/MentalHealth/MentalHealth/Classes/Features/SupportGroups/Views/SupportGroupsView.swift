//
//  SupportGroupsView.swift
//  MentalHealth
//
//  Created by alexcampean on 07.03.2022.
//  Copyright © 2022 alexcampean. All rights reserved.
//

import SwiftUI
import CoreLocation

struct SupportGroupsView: View {
  @EnvironmentObject var dependencies: SupportGroupsFeatureDependencies
  @StateObject var viewModel: SupportGroupViewModel
  @State private var searchText = ""
  @State var isPresentingDetails = false
  // TODO: move this to presentation layer
  @State var showFilters = false
  
  var body: some View {
    NavigationView {
      VStack {
        listView(with: viewModel.presentationState.currentValue ?? [])
          .disabled(viewModel.presentationState.isLoading)
          .overlay {
            if viewModel.presentationState.isLoading {
              ProgressView()
                .frame(maxWidth: .infinity,
                       maxHeight: .infinity)
                .background(ColorsCatalog.listBackground)
            }
          }
          .alert(isPresented: .constant(viewModel.presentationState.isFailed),
                 error: viewModel.presentationState.failureReason,
                 actions: { _ in
            Button("OK", role: .cancel) { }
          },
                 message: { error in
            Text(error.failureReason ?? String())
            
          })
      }
      .navigationTitle(viewModel.listTitle)
      .searchable(text: $searchText,
                  placement: .navigationBarDrawer(displayMode: .always),
                  prompt: viewModel.searchbarHintText)
      .toolbar {
        ToolbarItemGroup(placement: .navigationBarTrailing) {
          temporaryActions()
          Button {
            showFilters = true
          }
        label: {
          Image("Filter")
        }
        .accentColor(ColorsCatalog.primaryText)
        }
      }
      .background(ColorsCatalog.listBackground)
      .sheet(isPresented: $showFilters) {
        NavigationView {
          SupportGroupsFilterView()
            .toolbar {
              Button {
                self.showFilters.toggle()
              } label: {
                Image("Close")
              }
              .foregroundColor(ColorsCatalog.primaryText)
            }
        }
      }
    }
  }
  
  private func listView(with sections: [SupportGroupSectionUIModel]) -> some View {
    typealias DetailsView = SupportGroupsEventDetailsView
    typealias DetailsViewModel = SupportGroupEventDetailsViewModel
    var selectedItem = ""
    return ScrollView {
      // FIXME: The initial approach with LazyVStack didn't work because LazyVStack doesn't respond to changes
      VStack(alignment: .leading, spacing: 16.0) {
        ForEach(viewModel.presentationState.currentValue ?? []) { section in
          Section(header: SectionHeaderView(text: section.title)) {
            ForEach(section.items) { item in
              SupportGroupListItem(model: item)
                .onTapGesture {
                  selectedItem = item.id
                  isPresentingDetails.toggle()
                }
            }
          }
        }
        NavigationLink(destination: DetailsView(viewModel: DetailsViewModel(service: dependencies.service,
                                                                            state: dependencies.state,
                                                                            mapper: dependencies.mapper, geocoder: dependencies.geocoder,
                                                                            eventID: selectedItem)),
                       isActive: $isPresentingDetails) {
          EmptyView()
        }
      }
      .padding(.horizontal, 24.0)
      .frame(maxWidth: .infinity, maxHeight: .infinity)
    }
    .overlay {
      if sections.isEmpty {
        Text(viewModel.emptyListText)
          .padding(24.0)
      }
    }
  }
}

struct SupportGroupsView_Previews: PreviewProvider {
  static var previews: some View {
    let dtoMapper = DefaultSupportGroupsDTOMapper()
    let repository = MockedSupportGroupsRepository(timeInterval: 3.0,
                                                   mapper: dtoMapper)
    let tagsRepository = TagsMockedRepository(interval: 1.0)
    let state = SupportGroupsState()
    let service = DefaultSupportGroupsService(supportGroupsState: state,
                                              supportGroupsRepository: repository,
                                              tagsRepository: tagsRepository)
    let mapper = DefaultSupportGroupsUIMapper()
    let viewModel = SupportGroupViewModel(service: service, state: state, mapper: mapper)
    return SupportGroupsView(viewModel: viewModel)
  }
}

extension SupportGroupsView {
  private func temporaryActions() -> some View {
    HStack {
      Button(action: {
        viewModel.refresh()
      }) {
        Image(systemName: "arrow.triangle.2.circlepath.circle")
          .foregroundColor(ColorsCatalog.primaryText)
      }
      Button(action: {
        viewModel.addEvent()
      }) {
        Image("Add")
          .foregroundColor(ColorsCatalog.primaryText)
      }
      Button(action: {
        viewModel.deleteEvent()
      }) {
        Image("Delete")
          .foregroundColor(ColorsCatalog.primaryText)
      }
    }
  }
}
