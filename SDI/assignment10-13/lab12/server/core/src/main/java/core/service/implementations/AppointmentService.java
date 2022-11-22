package core.service.implementations;

import core.entity.Appointment;
import core.entity.ClinicException;
import core.entity.Pet;
import core.entity.Vet;
import core.repository.IAppointmentRepository;
import core.repository.IPetRepository;
import core.repository.IVetRepository;
import core.service.interfaces.IAppointmentService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Service
public class AppointmentService implements IAppointmentService {
    // Dependencies
    @Autowired
    private IAppointmentRepository appointmentRepository;
    @Autowired
    private IPetRepository petRepository;
    @Autowired
    private IVetRepository vetRepository;
    // Logger
    public static final Logger log = LoggerFactory.getLogger(AppointmentService.class);

    @Override
    @Transactional
    public List<Appointment> getAppointments() {
        log.trace("getAppointments --- method started");
        List<Appointment> result = appointmentRepository.findAll();
        log.trace("getAppointments --- method finished: result={}", result);
        return result;
    }

    @Override
    @Transactional
    // Transactions mean all or nothing. If there is an exception thrown somewhere in the method, changes are not persisted in the database. Something called rollback happens.
    public void addAppointment(Long petId, Long vetId, String type, String date) {
        log.trace("addAppointment --- method started: petId={}, vetId={}, type={}, date={}", petId, vetId, type, date);
        Pet pet = petRepository.findById(petId).orElseThrow(() -> new ClinicException("Pet doesn't exist"));
        Vet vet = vetRepository.findById(vetId).orElseThrow(() -> new ClinicException("Vet doesn't exist"));
        Appointment appointment = new Appointment(pet, vet, type, date);
        appointmentRepository.save(appointment);
        log.debug("addAppointment --- added: appointment={}", appointment);
        log.trace("addAppointment --- method finished");
    }

    @Override
    @Transactional
    public void deleteAppointment(Long id) {
        log.trace("deleteAppointment --- method started: id={}", id);
        appointmentRepository.findById(id).ifPresentOrElse(appointment -> {
            appointment.getPet().getAppointments().remove(appointment);
            appointment.getVet().getAppointments().remove(appointment);
            appointmentRepository.deleteById(id);
            appointmentRepository.flush();
            log.debug("deleteAppointment --- deleted: appointment={}", appointment);
        }, () -> {
            throw new ClinicException("Appointment does not exist");
        });
        log.trace("deleteAppointment --- method finished");
    }

    @Override
    @Transactional
    public void updateAppointment(Long id, Long petId, Long vetId, String type, String date) {
        log.trace("updateAppointment --- method started: id={}, petId={}, vetId={}, type={}, date={}", id, petId, vetId, type, date);
        appointmentRepository.findById(id).ifPresentOrElse(appointment -> {
            Pet pet = petRepository.findById(petId).orElseThrow(() -> new ClinicException("Pet doesn't exist"));
            Vet vet = vetRepository.findById(vetId).orElseThrow(() -> new ClinicException("Vet doesn't exist"));
            appointment.setPet(pet);
            appointment.setVet(vet);
            appointment.setType(type);
            appointment.setDate(date);
            log.debug("updateAppointment --- updated: appointment={}", appointment);
        }, () -> {
            throw new ClinicException("Appointment does not exist");
        });
        log.trace("updateAppointment --- method finished");
    }
}
