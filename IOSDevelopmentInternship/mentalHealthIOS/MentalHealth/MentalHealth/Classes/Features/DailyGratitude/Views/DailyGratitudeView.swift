//
//  DailyGratitudeView.swift
//  MentalHealth
//
//  Created by Mircea Vasiliniuc on 07.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import SwiftUI
import Alamofire

struct DailyGratitudeView: View {
  @EnvironmentObject var dependecies: DailyGratitudeFeatureDependencies
  @StateObject var viewModel: JournalEntriesViewModel
  @State var showAddEntryView = false
  
  var body: some View {
    NavigationView {
      VStack(alignment: .leading){
        listView(with: viewModel.presentationState.currentValue ?? [])
          .disabled(viewModel.presentationState.isLoading)
          .overlay {
            if viewModel.presentationState.isLoading {
              ProgressView()
                .frame(maxWidth: .infinity, maxHeight: .infinity)
                .background(ColorsCatalog.listBackground)
            }
          }
          .alert(isPresented: .constant(viewModel.presentationState.isFailed),
                 error: viewModel.presentationState.failureReason,
                 actions: { _ in
            Button("OK", role: .cancel) {}
          },
                 message: { error in
            Text(error.failureReason ?? String())
          })
      }
      .background(ColorsCatalog.listBackground)
      .navigationTitle(viewModel.listTitle)
      .toolbar {
        ToolbarItemGroup(placement: .navigationBarTrailing) {
          Button(action: {
            viewModel.refresh()
          }) {
            Image("Report")
              .foregroundColor(ColorsCatalog.primaryText)
          }
          Button(action: {
            showAddEntryView.toggle()
          }) {
            Image("Add")
              .foregroundColor(ColorsCatalog.primaryText)
          }
          .sheet(isPresented: $showAddEntryView) {
            JournalEntryAdditionView(viewModel: JournalEntriesAdditionViewModel(service: dependecies.service,
                                                                                state: dependecies.state))
          }
        }
      }
    }
  }
  
  private func listView(with sections: [JournalEntrySectionUIModel]) -> some View {
    ScrollView {
      LazyVStack(alignment: .leading, spacing: 16) {
        ForEach(sections) { section in
          Section(header: SectionHeaderView(text: section.title)) {
            ForEach(section.items) { entry in
              NavigationLink(destination: JournalEntryDetailsView(model: entry),
                             label: {
                JournalEntryView(model: entry)
              })
            }
          }
          .foregroundColor(ColorsCatalog.secondaryText)
        }
      }
      .padding(24.0)
    }
    .overlay {
      if sections.isEmpty {
        Text(viewModel.emptyListText)
          .padding(24.0)
      }
    }
  }
}

struct DailyGratitudeView_Previews: PreviewProvider {
  static var previews: some View {
    let state = DailyGratitudeState()
    let repo = DailyGratitudeMockedRepository(timeInterval: 1.0)
    let session: Alamofire.Session = .init()
    let tagsMapper = DefaultTagsDTOMapper()
    let tagsRepo = TagsServerRepository(session: session, mapper: tagsMapper)
    let service = DefaultDailyGratitudeService(repository: repo,
                                               tagsRepository: tagsRepo,
                                               state: state)
    let dependencies = DailyGratitudeFeatureDependencies(state: state, service: service)
    let viewModel = JournalEntriesViewModel(service: dependencies.service,
                                            state: dependencies.state)
    DailyGratitudeView(viewModel: viewModel)
  }
}
