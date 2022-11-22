//
//  MockedAppointmentsRepository.swift
//  BestFriendClinic
//
//  Created by Alex Campean on 11/14/22.
//

import Foundation
import Combine

class MockedAppointmentsRepository: AppointmentsRepository {
    // MARK: - Private Properties
    private var appointmets: [Appointment] = []
    private var timeInterval: TimeInterval
    
    // MARK: - Init
    init(timeInterval: TimeInterval) {
        self.timeInterval = timeInterval
        addMockedData()
    }
    
    // adds 10 mocked entries in the repository
    private func addMockedData() {
      appointmets = MockedAppointments().mockedData
    }
    
    func add(appointment: Appointment) -> AnyPublisher<Appointment, RepositoryError> {
        return Future<Appointment, RepositoryError> { promise in
            DispatchQueue.main.asyncAfter(deadline: .now() + self.timeInterval) {
                self.appointmets.append(appointment)
                promise(.success(appointment))
            }
        }.eraseToAnyPublisher()
    }
    
    func update(updatedAppointment: Appointment) -> AnyPublisher<Appointment, RepositoryError> {
        return Future<Appointment, RepositoryError> { promise in
            DispatchQueue.main.asyncAfter(deadline: .now() + self.timeInterval) {
                guard let index = self.appointmets.firstIndex(of: updatedAppointment) else {
                    promise(.failure(.entryNotFound))
                    return
                }
                self.appointmets[index] = updatedAppointment
                debugPrint(self.appointmets[index])
                promise(.success(updatedAppointment))
            }
        }.eraseToAnyPublisher()
    }
    
    func delete(appointment: Appointment) -> AnyPublisher<Appointment, RepositoryError> {
        return Future<Appointment, RepositoryError> { promise in
            DispatchQueue.main.asyncAfter(deadline: .now() + self.timeInterval) {
                guard let index = self.appointmets.firstIndex(of: appointment) else {
                    promise(.failure(.entryNotFound))
                    return
                }
                self.appointmets.remove(at: index)
                promise(.success(appointment))
            }
        }.eraseToAnyPublisher()
    }
    
    func getAll() -> AnyPublisher<[Appointment], RepositoryError> {
        return Future<[Appointment], RepositoryError> { promise in
            DispatchQueue.main.asyncAfter(deadline: .now() + self.timeInterval) {
                promise(.success(self.appointmets))
            }
        }.eraseToAnyPublisher()
    }
}
