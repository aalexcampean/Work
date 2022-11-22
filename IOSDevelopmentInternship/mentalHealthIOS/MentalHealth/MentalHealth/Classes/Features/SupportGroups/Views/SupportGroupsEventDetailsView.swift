//
//  SupportGroupsEventDetailsView.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 30.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import SwiftUI
import CoreLocation

struct SupportGroupsEventDetailsView: View {
  @StateObject var viewModel: SupportGroupEventDetailsViewModel
  @Environment(\.openURL) var openURL
  
  private let locationImageString = "Location"
  
  var body: some View {
    detailsView(with: viewModel.presentationState.currentValue)
      .overlay {
        if viewModel.presentationState.isLoading {
          ProgressIndicator()
        }
      }
      .navigationBarTitleDisplayMode(.inline)
      .alert(isPresented: .constant(viewModel.presentationState.isFailed),
             error: viewModel.presentationState.failureReason,
             actions: { _ in
        Button("OK", role: .cancel) { }
      },
             message: { error in
        Text(error.failureReason ?? String())
        
      })
  }
  
  private func detailsView(with model: SupportGroupItemUIModel?) -> some View {
    let defaultSupportGroupEventImage = "SupportGroupListItem"
    return ZStack {
      if let model = model {
        ScrollView {
          VStack(alignment: .leading, spacing: 28.0) {
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
            
            VStack(alignment: .leading, spacing: 32.0) {
              informations(with: model)
              
              aboutSection(description: model.description)
              
              if model.hasParticipants {
                participantsSection(participants: model.participants)
              }
              
              Spacer()
            }
            .padding(24.0)
          }
        }
        
        .toolbar {
          ToolbarItem(placement: .navigationBarTrailing) {
            bookmarkButton(with: model)
          }
        }
        
        floatingButton(with: model)
        
      } else {
        EmptyView()
      }
    }
  }
  
  // MARK: - Floating Button
  
  private func floatingButton(with model: SupportGroupItemUIModel) -> some View {
    let isJoined = model.attributes.elements.first(where: { item in
      if case .isJoined = item {
        return true
      }
      return false
    })
    return FloatingButton(text: model.joinActionTitle,
                          action: viewModel.handleJoinButtonPress,
                          maxHeight: 50.0,
                          foregroundColor: .white,
                          font: FontsCatalog.confirmationButton,
                          clipShape: RoundedRectangle(cornerRadius: 12.0),
                          backgroundColor: isJoined == nil ? ColorsCatalog.accent
                          : ColorsCatalog.buttonDisabled)
      .padding(.horizontal, 26.0)
      .padding(.bottom, 12.0)
  }
  
  // MARK: - Event Informations
  
  private func informations(with model: SupportGroupItemUIModel) -> some View {
    return VStack(alignment: .leading, spacing: 16.0) {
      Text(model.title)
        .foregroundColor(ColorsCatalog.primaryText)
        .font(FontsCatalog.heading1)
      
      dateTimeAndLocationSection(with: model)
    }
  }
  
  private func dateTimeAndLocationSection(with model: SupportGroupItemUIModel) -> some View {
    let calendarImage = "Calendar"
    
    return VStack(alignment: .leading, spacing: 8.0) {
      Button {
        self.viewModel.requestCalendarAccess()
        if let validUrl = URL(string: model.calendarUrl) {
          openURL(validUrl)
        }
      } label: {
        Label {
          Text("\(viewModel.occurrence):\n\(model.startDateExtended)")
            .font(FontsCatalog.listItemDateAndHour2)
            .foregroundColor(ColorsCatalog.secondaryText)
        } icon: {
          Image(calendarImage)
            .resizable()
            .aspectRatio(contentMode: .fit)
            .frame(height: 14.0)
            .foregroundColor(ColorsCatalog.secondaryText)
        }
      }
      
      if model.location == "online" {
        onlineRedirection(location: model.location, link: model.link)
      } else {
        onsiteLocation(with: model)
      }
    }
  }
  
  private func aboutSection(description: String) -> some View {
    return VStack(alignment: .leading, spacing: 4.0) {
      Text(viewModel.aboutSectionTitle)
        .font(FontsCatalog.heading3)
        .foregroundColor(ColorsCatalog.primaryText)
      Text(description)
        .font(FontsCatalog.paragraph)
        .foregroundColor(ColorsCatalog.secondaryText)
    }
  }
  
  private func participantsSection(participants: [ImageSource]) -> some View {
    return VStack(alignment: .leading, spacing: 12.0) {
      Text("\(viewModel.participantsTitle) (\(participants.count))")
        .font(FontsCatalog.heading3)
        .foregroundColor(ColorsCatalog.primaryText)
      ImageCarousel(imageSources: participants,
                    width: 88.0,
                    height: 88.0,
                    clipShape: Circle(),
                    showIndicators: false)
    }
  }
  
  private func onsiteLocation(with model: SupportGroupItemUIModel) -> some View {
    let locationImageString = "Location"
    
    return Button {
      viewModel.getLocationURL(locationString: model.location, completionHandler: { urlString in
        if let url = URL(string: urlString) {
          openURL(url)
        }
      })
    } label: {
      Label {
        Text(model.location)
          .font(FontsCatalog.listItemDateAndHour2)
          .foregroundColor(ColorsCatalog.secondaryText)
      } icon: {
        Image(locationImageString)
          .resizable()
          .aspectRatio(contentMode: .fit)
          .frame(height: 14.0)
          .foregroundColor(ColorsCatalog.secondaryText)
      }
    }
  }
  
  private func validURLRedirection(location: String,
                                   link: URL,
                                   imageString: String) -> some View {
    Link(destination: link, label: {
      labelLocationImage(location: location,
                         imageString: imageString)
    })
  }
  
  
  
  private func labelLocationImage(location: String,
                                  imageString: String) -> some View {
    Label {
      Text(location)
        .font(FontsCatalog.listItemDateAndHour2)
        .foregroundColor(ColorsCatalog.secondaryText)
    } icon: {
      Image(imageString)
        .resizable()
        .aspectRatio(contentMode: .fit)
        .frame(height: 14.0)
        .foregroundColor(ColorsCatalog.secondaryText)
    }
  }
  
  private func onlineRedirection(location: String, link: URL?) -> some View {
    if let link = link {
      return AnyView(validURLRedirection(location: location,
                                         link: link,
                                         imageString: locationImageString))
    } else {
      return AnyView(labelLocationImage(location: location,
                                        imageString: locationImageString))
    }
  }

  private func bookmarkButton(with model: SupportGroupItemUIModel) -> some View {
    let isBookmarked = model.attributes.elements.first(where: { item in
      if case .isBookmarked = item {
        return true
      }
      return false
    })
    
  let bookmarkImageString = isBookmarked != nil ? "RemoveBookmark" : "AddBookmark"
    
    return Button {
      viewModel.handleBookmarkButtonPress()
    } label: {
      Image(bookmarkImageString)
    }
    .foregroundColor(ColorsCatalog.primaryText)
  }
}

// MARK: - Details Preview

struct SupportGroupsEventDetailsView_Previews: PreviewProvider {
  static var previews: some View {
    typealias DetailsViewModel = SupportGroupEventDetailsViewModel
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
    let dtoMapper = DefaultSupportGroupsDTOMapper()
    let repository = MockedSupportGroupsRepository(timeInterval: 3.0,
                                                   mapper: dtoMapper)
    let tagsRepository = TagsMockedRepository(interval: 1.0)
    let state = SupportGroupsState()
    let service = DefaultSupportGroupsService(supportGroupsState: state,
                                              supportGroupsRepository: repository,
                                              tagsRepository: tagsRepository)
    let mapper = DefaultSupportGroupsUIMapper()
    let geocoder = CLGeocoder()
    return SupportGroupsEventDetailsView(viewModel: DetailsViewModel(service: service,
                                                                     state: state,
                                                                     mapper: mapper,
                                                                     geocoder: geocoder,
                                                                     eventID: model.id))
  }
}

private extension Image {
  
  func supportGroupResizeImage() -> some View {
    self
      .resizable()
      .scaledToFit()
  }
}
