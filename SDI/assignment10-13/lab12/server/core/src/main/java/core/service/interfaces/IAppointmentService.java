package core.service.interfaces;

import core.entity.Appointment;

import java.util.List;

public interface IAppointmentService {
    List<Appointment> getAppointments();

    void addAppointment(Long petId, Long vetId, String type, String date);
    void deleteAppointment(Long id);
    void updateAppointment(Long id, Long petId, Long vetId, String type, String date);
}
