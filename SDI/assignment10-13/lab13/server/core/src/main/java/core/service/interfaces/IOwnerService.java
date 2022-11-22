package core.service.interfaces;

import core.entity.Owner;
import core.entity.Pet;

import java.util.List;
import java.util.Set;

public interface IOwnerService {
    List<Owner> getOwners();
    Set<Pet> getOwnerPets(Long id);

    void addOwner(String firstName, String lastName, String email, String phoneNumber, String dateOfBirth);
    void deleteOwner(Long id);
    void updateOwner(Long id, String firstName, String lastName, String email, String phoneNumber, String dateOfBirth);
}
