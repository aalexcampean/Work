//
//  SupportGroupListItem.swift
//  MentalHealth
//
//  Created by alexcampean on 12.03.2022.
//  Copyright © 2022 alexcampean. All rights reserved.
//

import SwiftUI

struct SupportGroupListItem: View {
  private let model: SupportGroupItemUIModel
  
  init(model: SupportGroupItemUIModel) {
    self.model = model
  }
  
  var body: some View {
    let calendarImage = "Calendar"
    let defaultSupportGroupEventImage = "SupportGroupListItem"
    let bookmarkedImage = "Bookmarked"
    let joinedImage = "Joined"
    
    VStack(alignment: .leading, spacing: 0.0) {
      HStack(alignment: .center, spacing: 16.0) {
        switch model.image {
        case .url(let source):
          AsyncImage(url: source) { img in
            img
              .supportGroupResizeImage()
          } placeholder: {
            ProgressView()
              .progressViewStyle(.circular)
              .frame(width: 88.0, height: 88.0)
          }
        case .asset(let name):
          Image(name)
            .supportGroupResizeImage()
        case .system(let name):
          Image(systemName: name)
            .supportGroupResizeImage()
        case .placeholder:
          Image(defaultSupportGroupEventImage)
            .supportGroupResizeImage()
        }
        
        VStack(alignment: .leading, spacing: 8.0) {
          Text(model.title)
            .font(FontsCatalog.listItemTitle2)
            .foregroundColor(ColorsCatalog.primaryText)
          
          Label {
            Text(model.startDate)
              .font(FontsCatalog.listItemDateAndHour2)
              .foregroundColor(ColorsCatalog.secondaryText)
          } icon: {
            Image(calendarImage)
              .resizable()
              .aspectRatio(contentMode: .fit)
              .frame(height: 14.0)
              .foregroundColor(ColorsCatalog.secondaryText)
          }
          
          if model.hasTags {
            HashTagsCollectionView(tags: model.tags)
            EmptyView()
          }
        }
      }
      .padding(EdgeInsets(top: 24.0, leading: 16.0, bottom: 24.0, trailing: 16.0))
      
      Rectangle()
        .frame(height: 1.0, alignment: .center)
        .foregroundColor(ColorsCatalog.listItemBorder)
      
      if model.hasAttributes {
        HStack {
          Spacer()
          
          ForEach(model.attributes.elements, id: \.self) { attribute in
            Label {
              switch attribute {
              case .isBookmarked(let value):
                Text(value)
                  .font(FontsCatalog.eventMarker)
                  .foregroundColor(ColorsCatalog.secondaryText)
              case .isJoined(let value):
                Text(value)
                  .font(FontsCatalog.eventMarker)
                  .foregroundColor(ColorsCatalog.secondaryText)
              }
            } icon: {
              switch attribute {
              case .isBookmarked:
                Image(bookmarkedImage)
                  .supportGroupResizeEventMarkerImage()
              case .isJoined:
                Image(joinedImage)
                  .supportGroupResizeEventMarkerImage()
              }
            }
          }
        }
        .padding(EdgeInsets(top: 10.0, leading: 16.0, bottom: 10.0, trailing: 16.0))
      }
    }
    .background(ColorsCatalog.listItemBackground)
    .shadow(color: ColorsCatalog.listItemShadow, radius: 8.0, x: 0.0, y: 4.0)
    .cornerRadius(8.0)
    .overlay(
      RoundedRectangle(cornerRadius: 8.0, style: .continuous)
        .stroke(ColorsCatalog.listItemBorder, lineWidth: 1.0))
  }
}

struct SupportGroupListItem_Previews: PreviewProvider {
  static var previews: some View {
    let bookmarkedString = NSLocalizedString("supportGroups.list.item.bookmarked", comment: "")
    let joinedString = NSLocalizedString("supportGroups.list.item.joined", comment: "")
    let model = SupportGroupItemUIModel(id: "1",
                                        title: "Mental Strength",
                                        image: .asset("SupportGroupsListItem"),
                                        startDate: "MAR 13 2022",
                                        startDateExtended: "Thu, March 13 2022, 09:30 AM",
                                        location: "Motilor 6, Cluj-Napoca",
                                        description: "",
                                        tags: [],
                                        attributes: [.isBookmarked(bookmarkedString),
                                                     .isJoined(joinedString)],
                                        joinActionTitle: "Join",
                                        participants: [],
                                        calendarUrl: "")
    SupportGroupListItem(model: model)
  }
}

private extension Image {
  
  func supportGroupResizeImage() -> some View {
    self
      .resizable()
      .scaledToFill()
      .frame(width: 88.0, height: 88.0)
      .cornerRadius(8.0)
  }
  
  func supportGroupResizeEventMarkerImage() -> some View {
    self
      .resizable()
      .aspectRatio(contentMode: .fit)
      .frame(height: 14.0)
      .foregroundColor(ColorsCatalog.accent)
  }
}
