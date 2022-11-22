//
//  SupportGroupsUIMapper.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 08.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

protocol SupportGroupsUIMapper {
  func convertToUIModel(from event: SupportGroupEvent,
                        participants: [ImageSource]) -> SupportGroupItemUIModel
}
