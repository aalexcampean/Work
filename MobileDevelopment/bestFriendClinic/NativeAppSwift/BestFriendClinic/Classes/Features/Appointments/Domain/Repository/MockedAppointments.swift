//
//  MockedAppointments.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/14/22.
//

import Foundation

struct MockedAppointments {
    let mockedData = [Appointment(id: "1",
                                  type: "Ears Cleaning",
                                  date: Date.now.generateRandomly(),
                                  location: "Str. Paris nr. 20",
                                  petName: "Abel",
                                  vetName: "Claudiu Marinescu",
                                  description: nil),
                      Appointment(id: "2",
                                  type: "Flee Wash",
                                  date: Date.now.generateRandomly(),
                                  location: "Str. Paris nr. 20",
                                  petName: "Abel",
                                  vetName: "Irina Pop",
                                  description: nil),
                      Appointment(id: "3",
                                  type: "Total Wash",
                                  date: Date.now.generateRandomly(),
                                  location: "Str. Paris nr. 20",
                                  petName: "Ludmila",
                                  vetName: "Irina Pop",
                                  description: "She fell in a slime pull and noe her whole fur is full of sticky slime"),
                      Appointment(id: "4",
                                  type: "Haircut",
                                  date: Date.now.generateRandomly(),
                                  location: "Str. Paris nr. 20",
                                  petName: "Abel",
                                  vetName: "Mihai Ipate",
                                  description: nil),
                      Appointment(id: "5",
                                  type: "Teeth Cleaning",
                                  date: Date.now.generateRandomly(),
                                  location: "Str. Paris nr. 20",
                                  petName: "Snowflake",
                                  vetName: "Claudiu Marinescu",
                                  description: nil)]
}
