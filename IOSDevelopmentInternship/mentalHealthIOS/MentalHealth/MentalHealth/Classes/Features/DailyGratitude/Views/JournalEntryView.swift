//
//  JournalEntryView.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 13.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import SwiftUI

struct JournalEntryView: View {
  private let model: JournalEntryUIModel
  
  init (model: JournalEntryUIModel) {
    self.model = model
  }
  
  var body: some View {
    VStack(alignment: .leading, spacing: 8.0) {
      Text(model.publicationDate)
        .foregroundColor(ColorsCatalog.secondaryText)
        .font(FontsCatalog.listItemDate)
      
      Text(model.title)
        .foregroundColor(ColorsCatalog.primaryText)
        .font(FontsCatalog.listItemTitle)
        .multilineTextAlignment(.leading)
        .frame(maxWidth: .infinity, alignment: .leading)
      
      switch model.image {
      case .url(let source):
        AsyncImage(url: source) { img in
          img
            .frameJournalEntryMainScreenImage()
        } placeholder: {
          ProgressView()
            .progressViewStyle(.circular)
            .frame(width: 88.0, height: 88.0)
        }

      case .asset(let name):
        Image(name)
          .frameJournalEntryMainScreenImage()

      case .system(let name):
        Image(name)
          .frameJournalEntryMainScreenImage()

      case .placeholder:
        EmptyView()
      }
      
      if !model.tags.isEmpty {
        HashTagsCollectionView(tags: model.tags)
      }
    }
    .frame(maxWidth: .infinity)
    .padding(24.0)
    .background(ColorsCatalog.listItemBackground)
    .cornerRadius(8.0)
    .overlay {
      RoundedRectangle(cornerRadius: 8.0)
        .stroke(ColorsCatalog.listItemBorder, lineWidth: 1)
    }
    .shadow(color: ColorsCatalog.listItemShadow, radius: 8.0)
  }
}

struct JournalEntryView_Previews: PreviewProvider {
  static var previews: some View {
    let tag1 = TagUIModel(id: "1", text: "anxious", isSelected: false)
    let tag2 = TagUIModel(id: "2", text: "stressed", isSelected: false)
    let tag3 = TagUIModel(id: "3", text: "confused", isSelected: false)
    
    VStack {
      JournalEntryView(model: JournalEntryUIModel(id: "1",
                                                  title: "My inner motivation to get better",
                                                  image: .placeholder,
                                                  publicationDate: "June 20 2022",
                                                  tags: [],
                                                  associatedImages: []))
      
      JournalEntryView(model: JournalEntryUIModel(id: "2",
                                                  title: "I felt a little anxious when my boss gave me too many things to do this morning.",
                                                  image:.url(URL(string: "https://media.istockphoto.com/photos/saint-michaels-cathedral-at-dawn-picture-id184857397?b=1&k=20&m=184857397&s=170667a&w=0&h=0I08ERqlbmtZ1AQXvRK4JMQnOS7WigyAxr3j5d4woJw=")!),
                                                  publicationDate: "June 22 2022",
                                                  tags: [tag1, tag2],
                                                  associatedImages: []))
      
      JournalEntryView(model: JournalEntryUIModel(id: "3",
                                                  title: "I felt a little anxious when my boss gave me too many things to do this morning.",
                                                  image: .asset("SupportGroupListItem"),
                                                  publicationDate: "June 22 2022",
                                                  tags: [tag3],
                                                  associatedImages: []))
    }
  }
}

private extension Image {
  func frameJournalEntryMainScreenImage() -> some View {
    self
      .resizable()
      .scaledToFill()
      .frame(height: 96.0)
      .cornerRadius(8.0)
  }
}
