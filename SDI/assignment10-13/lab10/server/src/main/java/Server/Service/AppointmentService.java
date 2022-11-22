package Server.Service;

import Common.Model.Domain.Appointment;
import Common.Model.Validators.ValidatorException;
import Server.Repository.IRepository;

import java.util.Random;

public class AppointmentService {
    private IRepository<Long, Appointment> appointmentRepository;

    public AppointmentService(IRepository<Long, Appointment> appointmentRepository) {
        this.appointmentRepository = appointmentRepository;
    }

    public Iterable<Appointment> getAppointments() {
        return appointmentRepository.findAll();
    }

    public void addAppointment(Long petId, Long vetId, String type, String date) {
        Appointment appointment = new Appointment(new Random().nextInt(1000), petId, vetId, type, date);
        appointmentRepository.save(appointment);
    }

    public void deleteAppointment(Long id) {
        appointmentRepository.delete(id).orElseThrow(() -> {
            throw new ValidatorException("Appointment does not exist");
        });
    }

    public void updateAppointment(Long id, Long petId, Long vetId, String type, String date) {
        Appointment appointment = new Appointment(id, petId, vetId, type, date);
        appointmentRepository.update(appointment);
    }
}
