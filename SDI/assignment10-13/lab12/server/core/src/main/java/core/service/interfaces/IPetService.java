package core.service.interfaces;

import core.entity.Appointment;
import core.entity.Owner;
import core.entity.Pet;

import java.util.List;
import java.util.Set;

public interface IPetService {
    List<Pet> getPets();
    Owner getPetOwner(Long id);
    Set<Appointment> getPetAppointments(Long id);

    void addPet(String species, String breed, String name, String dateOfEnrolment, long ownerId);
    void deletePet(Long id);
    void updatePet(Long id, String species, String breed, String name, String dateOfEnrolment, long ownerId);
}
