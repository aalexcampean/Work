//
//  DailyGratitudeState.swift
//  MentalHealth
//
//  Created by alexcampean on 29.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

class DailyGratitudeState: ObservableObject {
  @Published var journalState:
  LoadingState<[DailyGratitudeJournalEntry], RepositoryError> = .loading()
}
