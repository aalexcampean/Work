//
//  HashTagsCollectionView.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 17.03.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import SwiftUI

struct HashTagsCollectionView: View {
  typealias TapHandler = (TagUIModel) -> Void
  var tags: [TagUIModel]
  var onTap: TapHandler? = nil
  
  var body: some View {
    FlexibleView(data: tags,
                 spacing: 8.0,
                 alignment: .leading) { item in
      HashTagView(text: item.text,
                  textColor: ColorsCatalog.secondaryText,
                  textFont: FontsCatalog.tag,
                  isSelected: item.isSelected)
        .onTapGesture {
          onTap?(item)
        }
    }
  }
}


struct HashTagsCollectionView_Previews: PreviewProvider {
  static var previews: some View {
    var tagsUI: [TagUIModel] = [TagUIModel(id: "1", text: "happiness"),
                                           TagUIModel(id: "2",text: "sadness"),
                                           TagUIModel(id: "3", text: "anger"),
                                           TagUIModel(id: "4", text: "pride"),
                                           TagUIModel(id: "5", text: "excitement"),
                                           TagUIModel(id: "6", text: "disgust"),
                                           TagUIModel(id: "7", text: "surprise"),
                                           TagUIModel(id: "8", text: "shame"),
                                           TagUIModel(id: "9", text: "fear"),
                                           TagUIModel(id: "10", text: "embarrasment")]
    HashTagsCollectionView(tags: tagsUI)
  }
}

