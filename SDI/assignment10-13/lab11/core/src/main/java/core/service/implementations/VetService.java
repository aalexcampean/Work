package core.service.implementations;

import core.entity.Appointment;
import core.entity.ClinicException;
import core.entity.Pet;
import core.entity.Vet;
import core.repository.IAppointmentRepository;
import core.repository.IPetRepository;
import core.repository.IVetRepository;
import core.service.interfaces.IVetService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

@Service
public class VetService implements IVetService {
    // Dependencies
    @Autowired
    private IVetRepository vetRepository;
    @Autowired
    private IAppointmentRepository appointmentRepository;
    @Autowired
    private IPetRepository petRepository;
    // Logger
    public static final Logger log = LoggerFactory.getLogger(VetService.class);

    @Override
    @Transactional
    public List<Vet> getVets() {
        log.trace("getVets --- method started");
        List<Vet> result = vetRepository.findAll();
        log.trace("getVets --- method finished: result={}", result);
        return result;
    }

    @Override
    @Transactional
    public Set<Appointment> getVetAppointments(Long id) {
        log.trace("getVetAppointments --- method started");
        Vet vet = vetRepository.findById(id).orElseThrow(() -> new ClinicException("Vet doesn't exist"));
        log.trace("getVetAppointments --- method finished: result={}", vet.getAppointments());
        return vet.getAppointments();
    }

    @Override
    @Transactional
    public Set<Pet> getVetPatients(Long id) {
        log.trace("getVetPatients --- method started");
        Vet vet = vetRepository.findById(id).orElseThrow(() -> new ClinicException("Vet doesn't exist"));
        Set<Pet> result = appointmentRepository.findAll().stream()
                .filter(appointment -> appointment.getVet().equals(vet))
                .map(appointment -> petRepository.findById(appointment.getPet().getId()).orElseThrow(() -> new ClinicException("Appointment doesn't exist")))
                .collect(Collectors.toSet());
        log.trace("getVetPatients --- method finished: result={}", result);
        return result;
    }

    @Override
    @Transactional
    public void addVet(String firstName, String lastName, String email, String phoneNumber, String dateOfBirth, int salary, int rating) {
        log.trace("addVet --- method started: firstName={}, lastName={}, email={}, phoneNumber={}, dateOfBirth={}, salary={}, rating={}", firstName, lastName, email, phoneNumber, dateOfBirth, salary, rating);
        Vet vet = new Vet(firstName, lastName, email, phoneNumber, dateOfBirth, salary, rating);
        vetRepository.save(vet);
        log.debug("addVet --- added: vet={}", vet);
        log.trace("addVet --- method finished");
    }

    @Override
    @Transactional
    public void deleteVet(Long id) {
        log.trace("deleteVet --- method started: id={}", id);
        vetRepository.findById(id).ifPresentOrElse(vet -> {
            vet.getAppointments().forEach(appointment -> {
                appointment.getPet().getAppointments().remove(appointment);
                vet.getAppointments().remove(appointment);
            });
            vetRepository.deleteById(id);
            vetRepository.flush();
            log.debug("deleteVet --- deleted: vet={}", vet);
        }, () -> {
            throw new ClinicException("Vet does not exist");
        });
        log.trace("deleteVet --- method finished");
    }

    @Override
    @Transactional
    public void updateVet(Long id, String firstName, String lastName, String email, String phoneNumber, String dateOfBirth, int salary, int rating) {
        log.trace("updateVet --- method started: id={}, firstName={}, lastName={}, email={}, phoneNumber={}, dateOfBirth={}, salary={}, rating={}", id, firstName, lastName, email, phoneNumber, dateOfBirth, salary, rating);
        vetRepository.findById(id).ifPresentOrElse(vet -> {
            vet.setFirstName(firstName);
            vet.setLastName(lastName);
            vet.setEmail(email);
            vet.setPhoneNumber(phoneNumber);
            vet.setDateOfBirth(dateOfBirth);
            vet.setSalary(salary);
            vet.setRating(rating);
            log.debug("updateVet --- updated: vet={}", vet);
        }, () -> {
            throw new ClinicException("Vet doesn't exist");
        });
        log.trace("updateVet --- method finished");
    }
}
