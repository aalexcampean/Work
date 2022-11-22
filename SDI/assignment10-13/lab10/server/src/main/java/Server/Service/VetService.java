package Server.Service;

import Common.Model.Domain.Appointment;
import Common.Model.Domain.Pet;
import Common.Model.Domain.Vet;
import Common.Model.Validators.ValidatorException;
import Server.Repository.IRepository;

import java.util.Random;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class VetService {
    private final IRepository<Long, Vet> vetRepository;
    private final IRepository<Long, Pet> petRepository;
    private final IRepository<Long, Appointment> appointmentRepository;

    public VetService(IRepository<Long, Vet> vetRepository, IRepository<Long, Pet> petRepository, IRepository<Long, Appointment> appointmentRepository) {
        this.vetRepository = vetRepository;
        this.petRepository = petRepository;
        this.appointmentRepository = appointmentRepository;
    }

    public Iterable<Vet> getVets() {
        return vetRepository.findAll();
    }

    public Iterable<Appointment> getVetAppointments(Long id) {
        return StreamSupport.stream(appointmentRepository.findAll().spliterator(), false)
                .filter(appointment -> appointment.getVetId() == id)
                .collect(Collectors.toList());
    }

    public Iterable<Pet> getVetPatients(Long id) {
        return StreamSupport.stream(appointmentRepository.findAll().spliterator(), false)
                .filter(appointment -> appointment.getVetId() == id)
                .map(appointment -> petRepository.findOne(appointment.getPetId()).get())
                .distinct()
                .collect(Collectors.toList());
    }

    public void addVet(String firstName, String lastName, String email, String phoneNumber, String dateOfBirth, int salary ,int rating) {
        Vet vet = new Vet(new Random().nextInt(1000), firstName, lastName, email, phoneNumber, dateOfBirth, salary, rating);
        vetRepository.save(vet);
    }

    public void deleteVet(Long id) {
        vetRepository.delete(id).orElseThrow(() -> {
            throw new ValidatorException("Vet does not exist");
        });
    }

    public void updateVet(Long id, String firstName, String lastName, String email, String phoneNumber, String dateOfBirth, int salary ,int rating) {
        Vet vet = new Vet(id, firstName, lastName, email, phoneNumber, dateOfBirth, salary, rating);
        vetRepository.update(vet);
    }
}
