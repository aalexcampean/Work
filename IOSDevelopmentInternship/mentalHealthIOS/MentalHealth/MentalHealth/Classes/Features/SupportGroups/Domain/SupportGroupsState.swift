//
//  SupportGroupsState.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 29.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

class SupportGroupsState: ObservableObject {
  @Published var eventsState: LoadingState<[SupportGroupEvent], RepositoryError> = .loading()
}
