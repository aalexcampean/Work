//
//  AppointmentsRepository.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/14/22.
//

import Foundation
import Combine

protocol AppointmentsRepository {
  func add(appointment: Appointment) -> AnyPublisher<Appointment, RepositoryError>
  func update(updatedAppointment: Appointment) -> AnyPublisher<Appointment, RepositoryError>
  func delete(appointment: Appointment) -> AnyPublisher<Appointment, RepositoryError>
  func getAll() -> AnyPublisher<[Appointment], RepositoryError>
}
