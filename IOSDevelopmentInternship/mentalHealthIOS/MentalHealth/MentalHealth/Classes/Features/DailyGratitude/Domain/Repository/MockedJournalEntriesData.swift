//
//  MockedJournalEntriesData.swift
//  MentalHealth
//
//  Created by alexcampean on 20.04.2022.
//  Copyright © 2022 nexttech. All rights reserved.
//

import Foundation

struct MockedJournalEntriesData {
  let mockedData = [DailyGratitudeJournalEntry(
                      identifier: "1",
                      title: "I'm grateful for having got the chance to sit down, relax and read a new book",
                      image: "https://images.unsplash.com/photo-1554774853-aae0a22c8aa4?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=2340&q=80",
                      publicationDate: Date.now.subtractedRandomly(),
                      tags: ["2", "5", "8"]),
                    DailyGratitudeJournalEntry(
                      identifier: "2",
                      title: "I'm grateful for speding time with my grandma",
                      image: nil,
                      publicationDate: Date.now.subtractedRandomly(),
                      tags: ["1", "6"]),
                    DailyGratitudeJournalEntry(
                      identifier: "3",
                      title: "Today I met up with Tom who I haven't seen in over 3 years",
                      image: nil,
                      publicationDate: Date.now.subtractedRandomly(),
                      tags: ["7"]),
                    DailyGratitudeJournalEntry(
                      identifier: "4",
                      title: "Exploring Norway has been such an incredible experience",
                      image: "https://images.unsplash.com/photo-1568888539200-ea13741b9e4d?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxzZWFyY2h8MTgwfHxpbnNwaXJpbmd8ZW58MHx8MHx8&auto=format&fit=crop&w=800&q=60",
                      publicationDate: Date.now.subtractedRandomly(),
                      tags: ["9", "5", "2", "8"]),
                    DailyGratitudeJournalEntry(
                      identifier: "5",
                      title: "My friends surprised me with plane tickets to Ancona for my birthday",
                      image: "https://images.unsplash.com/photo-1454496406107-dc34337da8d6?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=2600&q=80",
                      publicationDate: Date.now.subtractedRandomly(),
                      tags: ["7"]),
                    DailyGratitudeJournalEntry(
                      identifier: "6",
                      title: "I'm incredibly happy to have passed my driving exam",
                      image: nil,
                      publicationDate: Date.now.subtractedRandomly(),
                      tags: ["3", "5", "9"]),
                    DailyGratitudeJournalEntry(
                      identifier: "7",
                      title: "I adopted my first dog, Abel, today and I couldn't be happier",
                      image: "https://images.unsplash.com/photo-1596161751522-c2c14aeb4d69?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxzZWFyY2h8MjM5fHxpbnNwaXJpbmd8ZW58MHx8MHx8&auto=format&fit=crop&w=800&q=60",
                      publicationDate: Date.now.subtractedRandomly(),
                      tags: ["5", "1"]),
                    DailyGratitudeJournalEntry(
                      identifier: "8",
                      title: "Arizona surprised us with its beauty",
                      image: "https://images.unsplash.com/photo-1623080285406-5f0db64add8b?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=987&q=80",
                      publicationDate: Date.now.subtractedRandomly(),
                      tags: []),
                    DailyGratitudeJournalEntry(
                      identifier: "9",
                      title: "I always get surprised by how beautiful nature can be",
                      image: "https://images.unsplash.com/photo-1600101996439-5989a7563f35?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=2340&q=80",
                      publicationDate: Date.now.subtractedRandomly(),
                      tags: ["2", "8"])]
}
