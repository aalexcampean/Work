//
//  FloatingButton.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 08.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import SwiftUI

struct FloatingButton<Content: Shape>: View {
  typealias ActionHandler = () -> Void
  
  private let text: String
  private let maxWidth: CGFloat
  private let maxHeight: CGFloat
  private let foregroundColor: Color
  private let font: Font
  private let clipShape: Content
  private let backgroundColor: Color
  private let action: ActionHandler
  
  init(text: String,
       action: @escaping ActionHandler = {},
       maxWidth: CGFloat = .infinity,
       maxHeight: CGFloat,
       foregroundColor: Color = .white,
       font: Font = .title,
       clipShape: Content,
       backgroundColor: Color) {
    self.text = text
    self.maxWidth = maxWidth
    self.maxHeight = maxHeight
    self.foregroundColor = foregroundColor
    self.font = font
    self.clipShape = clipShape
    self.backgroundColor = backgroundColor
    self.action = action
  }
  
  var body: some View {
    VStack {
      Spacer()
      Button(action: action, label: {
        Text(text)
          .font(font)
          .frame(maxWidth: maxWidth, maxHeight: maxHeight)
          .foregroundColor(foregroundColor)
      })
        .background(backgroundColor)
        .clipShape(clipShape)
    }
  }
}

struct FloatingButton_Previews: PreviewProvider {
  static var previews: some View {
    FloatingButton(text: "Text",
                   maxWidth: .infinity,
                   maxHeight: 50.0,
                   foregroundColor:.white,
                   font: .title,
                   clipShape: RoundedRectangle(cornerRadius: 12.0),
                   backgroundColor: .accentColor)
  }
}
