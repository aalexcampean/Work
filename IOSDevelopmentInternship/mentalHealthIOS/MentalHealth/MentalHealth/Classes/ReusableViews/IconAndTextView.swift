//
//  IconAndTextView.swift
//  MentalHealth
//
//  Created by alexcampean on 14.03.2022.
//  Copyright © 2022 alexcampean. All rights reserved.
//

import SwiftUI

struct IconAndTextView: View {
    var image : Image
    var imageColor : Color
    
    var text : String
    var textColor : Color
    var textFont : Font
    
    var alignment : VerticalAlignment = .center
    var spacing : CGFloat = 8.0

    var body: some View {
        HStack(alignment: alignment, spacing: spacing) {
            image
                .resizable()
                .aspectRatio(contentMode: .fit)
                .frame(height: 14.0)
                .foregroundColor(imageColor)
            
            Text(text)
                .font(textFont)
                .foregroundColor(textColor)
        }
    }
}

struct IconAndTextView_Previews: PreviewProvider {
    static var previews: some View {
        VStack(alignment: .leading) {
            IconAndTextView(image: Image("Bookmarked"),
                            imageColor: Color("Accent"),
                            text: "Bookmarked",
                            textColor: Color("PrimaryText"),
                            textFont: Font.custom("Inter-Regular", size: 14.0))
            
            IconAndTextView(image: Image("Joined"),
                            imageColor: Color("Accent"),
                            text: "Joined",
                            textColor: Color("PrimaryText"),
                            textFont: Font.custom("Inter-Regular", size: 14.0))
            
            IconAndTextView(image: Image("Calendar"),
                            imageColor: Color("SecondaryText"),
                            text: "March 13, 09:30 AM",
                            textColor: Color("SecondaryText"),
                            textFont: Font.custom("Inter-Regular", size: 17.0))
            
            IconAndTextView(image: Image("Calendar"),
                            imageColor: Color("SecondaryText"),
                            text: "Next occurrence:\nThu, March 13 2022, 09:30 AM",
                            textColor: Color("SecondaryText"),
                            textFont: Font.custom("Inter-Regular", size: 17.0),
                            alignment: VerticalAlignment.top)
        }
    }
}
