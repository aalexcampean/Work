package Server.Service;

import Common.Model.Domain.Owner;
import Common.Model.Domain.Pet;
import Common.Model.Validators.ValidatorException;
import Server.Repository.IRepository;

import java.util.Random;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class OwnerService {
    private final IRepository<Long, Owner> ownerRepository;
    private final IRepository<Long, Pet> petRepository;

    public OwnerService(IRepository<Long, Owner> ownerRepository, IRepository<Long, Pet> petRepository) {
        this.ownerRepository = ownerRepository;
        this.petRepository = petRepository;
    }

    public Iterable<Owner> getOwners() {
        return ownerRepository.findAll();
    }

    public Iterable<Pet> getOwnerPets(Long id) {
        return StreamSupport.stream(petRepository.findAll().spliterator(), false)
                .filter(pet -> pet.getPersonId() == id)
                .collect(Collectors.toList());
    }

    public void addOwner(String firstName, String lastName, String email, String phoneNumber, String dateOfBirth) {
        Owner owner = new Owner(new Random().nextInt(1000), firstName, lastName, email, phoneNumber, dateOfBirth);
        ownerRepository.save(owner);
    }

    public void deleteOwner(Long id) {
        ownerRepository.delete(id).orElseThrow(() -> {
            throw new ValidatorException("Owner does not exist");
        });
    }

    public void updateOwner(Long id, String firstName, String lastName, String email, String phoneNumber, String dateOfBirth) {
        Owner owner = new Owner(id, firstName, lastName, email, phoneNumber, dateOfBirth);
        ownerRepository.update(owner);
    }
}
