package web.controller;

import core.dto.AppointmentDTO;
import core.dto.collections.AppointmentsDTO;
import core.service.interfaces.IAppointmentService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.stream.Collectors;

@RestController
public class AppointmentController {
    // Logger
    public static final Logger log = LoggerFactory.getLogger(AppointmentController.class);
    // Dependencies
    @Autowired
    private IAppointmentService appointmentService;

    @RequestMapping(value = "/appointments")
    AppointmentsDTO getAppointments() {
        log.trace("getAppointments --- method started");
        AppointmentsDTO result = new AppointmentsDTO(appointmentService.getAppointments()
                .stream()
                .map(appointment -> new AppointmentDTO().encode(appointment))
                .collect(Collectors.toSet()));
        log.trace("getAppointments --- method finished: result={}", result);
        return result;
    }

    @RequestMapping(value = "/appointments", method = RequestMethod.POST)
    void addAppointments(@RequestBody AppointmentDTO appointmentDTO) {
        log.trace("addAppointments --- method entered: appointmentDTO={}", appointmentDTO);
        appointmentService.addAppointment(appointmentDTO.getPetId(), appointmentDTO.getVetId(), appointmentDTO.getType(),
                appointmentDTO.getDate());
        log.trace("addAppointments --- method finished");
    }

    @RequestMapping(value = "/appointments/{id}", method = RequestMethod.DELETE)
    void deleteAppointments(@PathVariable Long id) {
        log.trace("deleteAppointments --- method entered: id={}", id);
        appointmentService.deleteAppointment(id);
        log.trace("deleteAppointments --- method finished");
    }

    @RequestMapping(value = "/appointments/{id}", method = RequestMethod.PUT)
    void updateAppointments(@PathVariable Long id, @RequestBody AppointmentDTO appointmentDTO) {
        log.trace("updateAppointments --- method entered: id={}, appointmentDTO={}", id, appointmentDTO);
        appointmentService.updateAppointment(id, appointmentDTO.getPetId(), appointmentDTO.getVetId(), appointmentDTO.getType(),
                appointmentDTO.getDate());
        log.trace("updateAppointments --- method finished");
    }
}
