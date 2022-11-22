//
//  ImageCarousel.swift
//  MentalHealth
//
//  Created by Tarciziu Gologan on 07.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import SwiftUI

struct ImageCarousel<Content: Shape>: View {
  let showIndicators: Bool
  let imageSources: [ImageSource]
  let width: CGFloat
  let height: CGFloat
  let clipShape: Content
  
  init(imageSources: [ImageSource],
       width: CGFloat,
       height: CGFloat,
       clipShape: Content,
       showIndicators: Bool = true) {
    self.showIndicators = showIndicators
    self.imageSources = imageSources
    self.width = width
    self.height = height
    self.clipShape = clipShape
  }
  
  var body: some View {
    ScrollView(.horizontal, showsIndicators: showIndicators) {
      LazyHStack {
        ForEach(imageSources, id: \.self) { image in
          switch image {
          case .url(let url):
            AsyncImage(url: url) { img in
              img
                .resizeCarouselImage(width: width,
                                     height: height,
                                     clipShape: clipShape)
            } placeholder: {
              ProgressView()
                .frame(width: width, height: height)
            }
          case .asset(let imageString):
            Image(imageString)
              .resizeCarouselImage(width: width,
                                   height: height,
                                   clipShape: clipShape)
          case .system(let imageString):
            Image(systemName: imageString)
              .resizeCarouselImage(width: width,
                                   height: height,
                                   clipShape: clipShape)
          case .placeholder:
            EmptyView()
          }
          
        }
      }
    }
  }
}

extension Image {
  fileprivate func resizeCarouselImage<Content: Shape>(width: CGFloat,
                                                       height: CGFloat,
                                                       clipShape: Content) -> some View {
    self
      .resizable()
      .frame(width: width, height: height)
      .scaledToFill()
      .clipShape(clipShape)
  }
}

struct ImageCarousel_Previews: PreviewProvider {
  static var previews: some View {
    let imageSources = [ImageSource.url(URL(string: "https://images.unsplash.com/photo-1501196354995-cbb51c65aaea?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=1471&q=80")!),
                ImageSource.url(URL(string: "https://images.unsplash.com/photo-1580489944761-15a19d654956?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=761&q=80")!),
                ImageSource.url(URL(string: "https://images.unsplash.com/photo-1522529599102-193c0d76b5b6?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=1470&q=80")!),
                ImageSource.url(URL(string: "https://images.unsplash.com/photo-1500648767791-00dcc994a43e?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=687&q=80")!),
                ImageSource.url(URL(string: "https://images.unsplash.com/photo-1523824921871-d6f1a15151f1?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=687&q=80")!),
                ImageSource.url(URL(string: "https://images.unsplash.com/photo-1474176857210-7287d38d27c6?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=1470&q=80")!)]
    ImageCarousel(imageSources: imageSources,
                  width: 88.0,
                  height: 88.0,
                  clipShape: Circle())
  }
}
