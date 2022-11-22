package core.service.implementations;

import core.entity.*;
import core.repository.IOwnerRepository;
import core.repository.IPetRepository;
import core.service.interfaces.IPetService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Set;

@Service
public class PetService implements IPetService {
    // Logger
    public static final Logger log = LoggerFactory.getLogger(PetService.class);
    // Dependencies
    @Autowired
    private IPetRepository petRepository;
    @Autowired
    private IOwnerRepository ownerRepository;

    @Override
    @Transactional
    public List<Pet> getPets() {
        log.trace("getPets --- method started");
        List<Pet> result = petRepository.findAll();
        log.trace("getPets --- method finished: result={}", result);
        return result;
    }

    @Override
    @Transactional
    public BirthCertificate getPetBirthCertificate(Long id) {
        log.trace("getPetBirthCertificate --- method started");
        Pet pet = petRepository.findById(id).orElseThrow(() -> new ClinicException("Pet doesn't exist"));
        log.trace("getPetBirthCertificate --- method finished: result={}", pet.getBirthCertificate());
        return pet.getBirthCertificate();
    }

    @Override
    @Transactional
    public Owner getPetOwner(Long id) {
        log.trace("getPetOwner --- method started: id={}", id);
        Pet pet = petRepository.findById(id).orElseThrow(() -> new ClinicException("Pet doesn't exist"));
        log.trace("getPetOwner --- method finished: result={}", pet.getOwner());
        return pet.getOwner();
    }

    @Override
    @Transactional
    public Set<Appointment> getPetAppointments(Long id) {
        log.trace("getPetAppointments --- method started: id={}", id);
        Pet pet = petRepository.findById(id).orElseThrow(() -> new ClinicException("Pet doesn't exist"));
        log.trace("getPetAppointments --- method finished: result={}", pet.getAppointments());
        return pet.getAppointments();
    }

    @Override
    @Transactional
    public void addPet(String species, String breed, String name, String dateOfEnrolment, Long ownerId) {
        log.trace("addPet --- method started: species={}, breed={}, name={}, dateOfEnrolment={}, ownerId={}", species, breed, name, dateOfEnrolment, ownerId);
        ownerRepository.findById(ownerId).ifPresentOrElse(owner -> {
            Pet pet = new Pet(species, breed, name, dateOfEnrolment, owner);
            petRepository.save(pet);
            log.debug("addPet --- added: pet={}", pet);
        }, () -> {
            throw new ClinicException("Owner does not exist");
        });
        log.trace("addPet --- method finished");
    }

    @Override
    @Transactional
    public void deletePet(Long id) {
        log.trace("deletePet --- method started: id={}", id);
        petRepository.findById(id).ifPresentOrElse(pet -> {
            pet.getOwner().getPets().remove(pet);
            pet.getAppointments().forEach(appointment -> {
                appointment.getVet().getAppointments().remove(appointment);
                pet.getAppointments().remove(appointment);
            });
            petRepository.deleteById(id);
            petRepository.flush();
            log.debug("deletePet --- deleted: pet={}", pet);
        }, () -> {
            throw new ClinicException("Pet does not exist");
        });
        log.trace("deletePet --- method finished");
    }

    @Override
    @Transactional
    public void updatePet(Long id, String species, String breed, String name, String dateOfEnrolment, Long ownerId) {
        log.trace("updatePet --- method started: species={}, breed={}, name={}, dateOfEnrolment={}, ownerId={}", species, breed, name, dateOfEnrolment, ownerId);
        petRepository.findById(id).ifPresentOrElse(pet -> {
            Owner owner = ownerRepository.findById(ownerId).orElseThrow(() -> new ClinicException("Owner doesn't exist"));
            pet.setSpecies(species);
            pet.setBreed(breed);
            pet.setName(name);
            pet.setDateOfEnrolment(dateOfEnrolment);
            pet.setOwner(owner);
            log.debug("updatePet --- updated: pet={}", pet);
        }, () -> {
            throw new ClinicException("Appointment does not exist");
        });
        log.trace("updatePet --- method finished");
    }
}
