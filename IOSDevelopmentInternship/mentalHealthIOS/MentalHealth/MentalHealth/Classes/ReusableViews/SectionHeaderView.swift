//
//  SectionHeaderView.swift
//  MentalHealth
//
//  Created by alexcampean on 24.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import SwiftUI

struct SectionHeaderView: View {
  private let text: String
  
  init (text: String) {
    self.text = text
  }
  
  var body: some View {
    Text(text)
      .font(FontsCatalog.sectionTitle)
      .foregroundColor(ColorsCatalog.secondaryText)
  }
}

struct SectionHeaderView_Previews: PreviewProvider {
  static var previews: some View {
    SectionHeaderView(text: "")
  }
}
