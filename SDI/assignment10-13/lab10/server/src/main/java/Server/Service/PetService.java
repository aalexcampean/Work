package Server.Service;

import Common.Model.Domain.Appointment;
import Common.Model.Domain.Owner;
import Common.Model.Domain.Pet;
import Common.Model.Validators.ValidatorException;
import Server.Repository.IRepository;

import java.util.Objects;
import java.util.Optional;
import java.util.Random;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class PetService {
    private final IRepository<Long, Pet> petRepository;
    private final IRepository<Long, Owner> ownerRepository;
    private final IRepository<Long, Appointment> appointmentRepository;

    public PetService(IRepository<Long, Pet> petRepository, IRepository<Long, Owner> ownerRepository, IRepository<Long, Appointment> appointmentRepository) {
        this.petRepository = petRepository;
        this.ownerRepository = ownerRepository;
        this.appointmentRepository = appointmentRepository;
    }

    public Iterable<Pet> getPets() {
        return this.petRepository.findAll();
    }

    public Owner getPetOwner(Long id) {
        Long ownerId = StreamSupport.stream(this.petRepository.findAll().spliterator(), false)
                .filter(pet -> Objects.equals(pet.getId(), id))
                .map(Pet::getPersonId)
                .findAny()
                .orElse(null);

        Optional<Owner> owner = ownerRepository.findOne(ownerId);
        if (owner.isEmpty())
            throw new ValidatorException("Pet does not have an owner");
        return owner.get();
    }

    public Iterable<Appointment> getPetAppointments(Long id) {
        return StreamSupport.stream(appointmentRepository.findAll().spliterator(), false)
                .filter(appointment -> appointment.getPetId() == id)
                .collect(Collectors.toList());
    }

    public void addPet(String species, String breed, String name, String dateOfEnrolment, long personId) {
        Pet pet = new Pet(new Random().nextInt(1000), species, breed, name, dateOfEnrolment, personId);
        petRepository.save(pet);
    }

    public void deletePet(Long id) {
        petRepository.delete(id).orElseThrow(() -> {
            throw new ValidatorException("Pet does not exist");
        });
    }

    public void updatePet(Long id, String species, String breed, String name, String dateOfEnrolment, long personId) {
        Pet pet = new Pet(id, species, breed, name, dateOfEnrolment, personId);
        petRepository.update(pet);
    }
}
