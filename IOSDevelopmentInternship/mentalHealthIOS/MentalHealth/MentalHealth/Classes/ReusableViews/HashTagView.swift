//
//  HashTagView.swift
//  MentalHealth
//
//  Created by nexttech on 15.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import SwiftUI

struct HashTagView: View {
  var text : String
  var textColor : Color
  var textFont : Font
  var isSelected: Bool
  
  var body: some View {
    Text("#\(text)")
      .font(textFont)
      .foregroundColor(isSelected ? ColorsCatalog.accent : textColor)
      .padding(EdgeInsets(top: 4.0, leading: 8.0, bottom: 4.0, trailing: 8.0))
      .overlay(
        RoundedRectangle(cornerRadius: 7.0, style: .continuous)
          .stroke(isSelected ? ColorsCatalog.accent : textColor, lineWidth: 1.0))
  }
}

struct HashTagView_Previews: PreviewProvider {
  static var previews: some View {
    HStack{
      HashTagView(text: "motivation",
                  textColor: ColorsCatalog.secondaryText,
                  textFont: FontsCatalog.tag,
                  isSelected: false)
      HashTagView(text: "health",
                  textColor: ColorsCatalog.secondaryText,
                  textFont: FontsCatalog.tag,
                  isSelected: false)
    }
  }
}
