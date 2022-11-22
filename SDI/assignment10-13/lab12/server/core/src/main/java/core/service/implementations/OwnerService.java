package core.service.implementations;

import core.entity.ClinicException;
import core.entity.Owner;
import core.entity.Pet;
import core.repository.IOwnerRepository;
import core.service.interfaces.IOwnerService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Set;

@Service
public class OwnerService implements IOwnerService {
    // Logger
    public static final Logger log = LoggerFactory.getLogger(OwnerService.class);
    // Dependencies
    @Autowired
    private IOwnerRepository ownerRepository;

    @Override
    @Transactional
    public List<Owner> getOwners() {
        log.trace("getOwners --- method started");
        List<Owner> result = ownerRepository.findAll();
        log.trace("getOwners --- method finished: result={}", result);
        return result;
    }

    @Override
    @Transactional
    public Set<Pet> getOwnerPets(Long id) {
        log.trace("getOwnerPets --- method started: id={}", id);
        Owner owner = ownerRepository.findById(id).orElseThrow(() -> new ClinicException("Owner doesn't exist"));
        log.trace("getOwnerPets --- method finished: result={}", owner.getPets());
        Set<Pet> ownerPets = owner.getPets();
        return ownerPets;
    }

    @Override
    @Transactional
    public void addOwner(String firstName, String lastName, String email, String phoneNumber, String dateOfBirth) {
        log.trace("addOwner --- method started: firstname={}, lastname={}, email={}, phoneNumber={}, dateOfBirth={}", firstName, lastName, email, phoneNumber, dateOfBirth);
        Owner owner = new Owner(firstName, lastName, email, phoneNumber, dateOfBirth);
        ownerRepository.save(owner);
        log.debug("addOwner --- added: owner={}", owner);
        log.trace("addOwner --- method finished");
    }

    @Override
    @Transactional
    public void deleteOwner(Long id) {
        log.trace("deleteOwner --- method started: id={}", id);
        ownerRepository.findById(id).ifPresentOrElse(owner -> {
            ownerRepository.deleteById(id);
            log.debug("deleteOwner --- deleted: owner={}", owner);
        }, () -> {
            throw new ClinicException("Owner does not exist");
        });
        log.trace("deleteOwner --- method finished");
    }

    @Override
    @Transactional
    public void updateOwner(Long id, String firstName, String lastName, String email, String phoneNumber, String dateOfBirth) {
        log.trace("updateOwner --- method started: id={}, firstName={}, lastName={}, email={}, phoneNumber={}, dateOfBirth={}", id, firstName, lastName, email, phoneNumber, dateOfBirth);
        ownerRepository.findById(id).ifPresentOrElse(owner -> {
            owner.setFirstName(firstName);
            owner.setLastName(lastName);
            owner.setEmail(email);
            owner.setPhoneNumber(phoneNumber);
            owner.setDateOfBirth(dateOfBirth);
            log.debug("updateOwner --- updated: owner={}", owner);
        }, () -> {
            throw new ClinicException("Owner does not exist");
        });
        log.trace("updateOwner --- method finished");
    }
}
