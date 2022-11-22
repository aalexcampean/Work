//
//  MentalHealthApp.swift
//  MentalHealth
//
//  Created by Mircea Vasiliniuc on 07.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import SwiftUI
import Alamofire
import CoreLocation

class DailyGratitudeFeatureDependencies: ObservableObject {
  @Published var state: DailyGratitudeState
  @Published var service: DailyGratitudeService
  
  init(state: DailyGratitudeState, service: DailyGratitudeService) {
    self.state = state
    self.service = service
  }
}

class SupportGroupsFeatureDependencies: ObservableObject {
  private(set) var state: SupportGroupsState
  private(set) var service: SupportGroupsService
  private(set) var mapper: SupportGroupsUIMapper
  private(set) var geocoder: CLGeocoder
  
  init(state: SupportGroupsState,
       service: SupportGroupsService,
       mapper: SupportGroupsUIMapper,
       geocoder: CLGeocoder) {
    self.state = state
    self.service = service
    self.mapper = mapper
    self.geocoder = geocoder
  }
}

@main
struct MentalHealthApp: App {
  private var dailyGratitudeDependencies: DailyGratitudeFeatureDependencies = {
    let state = DailyGratitudeState()
    let session: Alamofire.Session = .default
    
    let tagsMapper = DefaultTagsDTOMapper()
    let tagsRepo = TagsServerRepository(session: session, mapper: tagsMapper)
    let tagsMockedRepo = TagsMockedRepository(interval: 3.0)
    
    let journalEntriesMapper = DefaultJournalEntryDTOMapper()
    let journalEntriesRepo = DailyGratitudeServerRepository(session: session, mapper: journalEntriesMapper)
    let journalEntriesMockedRepo = DailyGratitudeMockedRepository(timeInterval: 3.0)
    
    let service = DefaultDailyGratitudeService(repository: journalEntriesMockedRepo,
                                               tagsRepository: tagsMockedRepo,
                                               state: state)
    return DailyGratitudeFeatureDependencies(state: state, service: service)
  }()
  private var supportGroupsFeatureDependencies: SupportGroupsFeatureDependencies = {
    let session: Alamofire.Session = .init()
    let tagsSession: Alamofire.Session = .init()
    
    let dtoMapper = DefaultSupportGroupsDTOMapper()
    
    let repository = RealSupportGroupsRepository(session: session,
                                                 mapper: dtoMapper)
    
    let mockedRepository = MockedSupportGroupsRepository(timeInterval: 1.0,
                                                         mapper: dtoMapper)
    let tagsRepository = TagsServerRepository(session: tagsSession,
                                              mapper: DefaultTagsDTOMapper())
    let tagsMockedRepository = TagsMockedRepository(interval: 1.0)
    let state = SupportGroupsState()
    let service = DefaultSupportGroupsService(supportGroupsState: state,
                                              supportGroupsRepository: mockedRepository,
                                              tagsRepository: tagsMockedRepository)
    
    let mapper = DefaultSupportGroupsUIMapper()
    let geocoder = CLGeocoder()
    return SupportGroupsFeatureDependencies(state: state,
                                            service: service,
                                            mapper: mapper,
                                            geocoder: geocoder)
  }()
  
  var body: some Scene {
    WindowGroup {
      MainLandingView()
      /// Gives an Observable object to the subhierarchy
        .environmentObject(dailyGratitudeDependencies)
        .environmentObject(supportGroupsFeatureDependencies)
    }
  }
}
