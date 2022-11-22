//
//  MainLandingView.swift
//  MentalHealth
//
//  Created by Mircea Vasiliniuc on 07.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import SwiftUI

struct MainLandingView: View {
  @EnvironmentObject var dailyGratitudeDependencies: DailyGratitudeFeatureDependencies
  @EnvironmentObject var supportGroupsDependencies: SupportGroupsFeatureDependencies
  
  let dailyGratitudeTabTitle = NSLocalizedString("gratitudeJournal.list.title", comment: "")

  var body: some View {
    let supportGroupsTabTitle = NSLocalizedString("supportGroups.tab.title", comment: "")
    TabView {
      SupportGroupsView(viewModel: SupportGroupViewModel(service: supportGroupsDependencies.service,
                                                         state: supportGroupsDependencies.state,
                                                         mapper: supportGroupsDependencies.mapper))
        .tabItem {
          Label(supportGroupsTabTitle, image: "SupportGroup")
        }
      
      DailyGratitudeView(viewModel: JournalEntriesViewModel(service: dailyGratitudeDependencies.service,
                                                            state: dailyGratitudeDependencies.state))
        .tabItem {
          Label(dailyGratitudeTabTitle, image: "DailyGratitude")
        }
    }
  }
}

struct MainLandingView_Previews: PreviewProvider {
  static var previews: some View {
    MainLandingView()
  }
}
