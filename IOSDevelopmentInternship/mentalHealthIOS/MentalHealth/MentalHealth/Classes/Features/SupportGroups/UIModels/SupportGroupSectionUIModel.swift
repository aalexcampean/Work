//
//  SupportGroupsSectionUIModel.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 23.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

struct SupportGroupSectionUIModel: Identifiable {
  let id = UUID()
  let title: String
  let items: [SupportGroupItemUIModel]
}
