package core.service.interfaces;

import core.entity.Appointment;
import core.entity.Pet;
import core.entity.Vet;

import java.util.List;
import java.util.Set;

public interface IVetService {
    List<Vet> getVets();
    Set<Appointment> getVetAppointments(Long id);
    Set<Pet> getVetPatients(Long id);

    void addVet(String firstName, String lastName, String email, String phoneNumber, String dateOfBirth, Integer salary, Integer rating);
    void deleteVet(Long id);
    void updateVet(Long id, String firstName, String lastName, String email, String phoneNumber, String dateOfBirth, Integer salary, Integer rating);
}
