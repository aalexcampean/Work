//
//  JournalEntryDetailsView.swift
//  MentalHealth
//
//  Created by alexcampean on 29.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import SwiftUI

struct JournalEntryDetailsView: View {
  private let model: JournalEntryUIModel
  
  init (model: JournalEntryUIModel) {
    self.model = model
  }
  
  var body: some View {
    GeometryReader { geometry in
      VStack(alignment: .leading, spacing: 8.0) {
        dateView
        titleView
          .padding(EdgeInsets(top: 0, leading: 0, bottom: 8.0, trailing: 0))
        imageView(geometry: geometry)
        mockedCarouselView(geometry: geometry)
          .padding(EdgeInsets(top: 0, leading: 0, bottom: 8.0, trailing: 0))
        tagsView
        Spacer()
      }
      .padding(EdgeInsets(top: 0, leading: 24.0, bottom: 0, trailing: 24.0))
      .background(ColorsCatalog.listItemBackground)
      .toolbar {
        ToolbarItemGroup(placement: .navigationBarTrailing) {
          Button(action: {}) {
            Image("Delete")
              .foregroundColor(ColorsCatalog.primaryText)
          }
          Button(action: {}) {
            Image("Edit")
              .foregroundColor(ColorsCatalog.primaryText)
          }
        }
      }
    }
  }
  
  @ViewBuilder private var dateView: some View {
    Text(model.publicationDate)
      .foregroundColor(ColorsCatalog.secondaryText)
      .font(FontsCatalog.listItemDate)
  }
  
  @ViewBuilder private var titleView: some View {
    Text(model.title)
      .foregroundColor(ColorsCatalog.primaryText)
      .font(FontsCatalog.paragraph)
      .multilineTextAlignment(.leading)
      .padding(EdgeInsets(top: 0, leading: 0, bottom: 8.0, trailing: 0))
  }
  
  @ViewBuilder
  private func imageView(geometry: GeometryProxy) -> some View {
    switch model.image {
    case .url(let source):
      AsyncImage(url: source) { $0.frameJournalEntryDetailsImage(geometry: geometry) } placeholder: {
        ProgressView()
          .progressViewStyle(.circular)
      }
    case .asset(let name):
      Image(name)
        .frameJournalEntryDetailsImage(geometry: geometry)
    case .system(let name):
      Image(name)
        .frameJournalEntryDetailsImage(geometry: geometry)
    case .placeholder:
      EmptyView()
    }
  }
  
  @ViewBuilder
  private func mockedCarouselView(geometry: GeometryProxy) -> some View {
    if (model.image != .placeholder) {
      let clipShape = RoundedRectangle(cornerRadius: 8.0)
      VStack {
        ImageCarousel(imageSources: self.model.associatedImages,
                      width: geometry.size.width * 0.16,
                      height: geometry.size.height * 0.09,
                      clipShape: clipShape)
          .scaledToFit()
      }
    }
  }
  
  @ViewBuilder private var tagsView: some View {
    if !model.tags.isEmpty {
      HashTagsCollectionView(tags: model.tags)
    }
    EmptyView()
  }
}

private extension Image {
  func frameJournalEntryDetailsImage(geometry: GeometryProxy) -> some View {
    self
      .resizable()
      .scaledToFill()
      .frame(height: geometry.size.height * 0.25, alignment: .center)
      .cornerRadius(8.0)
  }
}

struct JournalEntryDetailsView_Previews: PreviewProvider {
  static var previews: some View {
    let tagModel = TagUIModel(id: "1", text: "I don't know what is happening", isSelected: false)
    let model = JournalEntryUIModel(id: "1",
                                    title: "Random Title",
                                    image: .url(URL(string: "https://images.unsplash.com/photo-1533558837877-f9a97ac5ba0c?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=1364&q=80")!),
                                    publicationDate: "June 22 2022",
                                    tags: [tagModel],
                                    associatedImages: [])
    JournalEntryDetailsView(model: model)
  }
}
