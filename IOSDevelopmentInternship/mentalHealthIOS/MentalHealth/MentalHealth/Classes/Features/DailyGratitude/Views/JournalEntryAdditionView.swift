//
//  JournalEntryAdditionView.swift
//  MentalHealth
//
//  Created by alexcampean on 28.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import SwiftUI

struct JournalEntryAdditionView: View {
  @StateObject var viewModel: JournalEntriesAdditionViewModel
  @Environment(\.presentationMode) private var presentationMode
  
  var body: some View {
    NavigationView {
      ZStack {
        ScrollView(showsIndicators: false) {
          VStack(alignment: .leading, spacing: 32.0) {
            VStack(alignment: .leading, spacing: 16.0) {
              textFieldPrompt
              
              VStack(alignment: .trailing, spacing: 4.0) {
                textFieldView
                textFieldCharacterCounterView
              }
            }
            .padding(.top, 38.0)
            
            VStack(alignment: .leading, spacing: 8.0) {
              tagsPrompt
              tagsView
            }
            
            VStack(alignment: .leading, spacing: 8.0) {
              mediaPrompt
              mediaIcon
            }
            Spacer()
          }
          .padding(EdgeInsets(top: 0, leading: 24, bottom: 0, trailing: 24))
        }
        saveButton
      }
      .navigationTitle(viewModel.addNewEntryTitle)
      .navigationBarTitleDisplayMode(.inline)
      .toolbar {
        Button {
          presentationMode.wrappedValue.dismiss()
        } label: {
          Image("Close")
        }
        .foregroundColor(ColorsCatalog.primaryText)
      }
    }
  }
  
  @ViewBuilder private var textFieldPrompt: some View {
    Text(viewModel.textPrompt)
      .font(FontsCatalog.listItemTitle)
  }
  
  @ViewBuilder private var textFieldView: some View {
    TextEditor(text: $viewModel.inputMessage)
      .overlay(
        RoundedRectangle(cornerRadius: 8.0, style: .continuous)
          .stroke(viewModel.isTextFieldSelected ? ColorsCatalog.accent : ColorsCatalog.primaryText)
      )
      .frame(height: 130.0)
      .onTapGesture {
        viewModel.selectTextField()
      }
  }
  
  @ViewBuilder private var textFieldCharacterCounterView: some View {
    Text("\(viewModel.inputMessage.count) / 100 characters")
      .font(FontsCatalog.characterCount)
      .foregroundColor(ColorsCatalog.secondaryText)
  }
  
  @ViewBuilder private var tagsPrompt: some View {
    Text("Tags")
      .font(FontsCatalog.listItemTitle)
  }
  
  @ViewBuilder private var tagsView: some View {
    HashTagsCollectionView(tags: viewModel.tagsUI, onTap: { tag in
      self.viewModel.selectTag(tagUiModel: tag)
    })
  }
  
  @ViewBuilder private var mediaPrompt: some View {
    Text("Media")
      .font(FontsCatalog.listItemTitle)
  }
  
  @ViewBuilder private var mediaIcon: some View {
    RoundedRectangle(cornerRadius: 8.0)
      .foregroundColor(ColorsCatalog.mediaBackground)
      .overlay(Button(action: {}) {
        Image("Media")
          .foregroundColor(ColorsCatalog.accent)
      })
      .frame(width: 63.0, height: 63.0, alignment: .center)
  }
  
  @ViewBuilder private var saveButton: some View {
    FloatingButton(text: viewModel.buttonTitle,
                   action: {viewModel.saveJournalEntry()
      presentationMode.wrappedValue.dismiss()},
                   maxHeight: 50.0,
                   foregroundColor: .white,
                   font: FontsCatalog.confirmationButton,
                   clipShape: RoundedRectangle(cornerRadius: 12.0),
                   backgroundColor: ColorsCatalog.accent)
      .padding(.horizontal, 26.0)
      .padding(.bottom, 12.0)
  }
}
