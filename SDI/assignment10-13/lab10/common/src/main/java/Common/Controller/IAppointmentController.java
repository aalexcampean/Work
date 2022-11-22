package Common.Controller;

import Common.Model.Domain.Appointment;

import java.util.concurrent.CompletableFuture;

public interface IAppointmentController extends IBaseController {
    String GET_APPOINTMENTS = "getAppointments";
    String ADD_APPOINTMENT = "addAppointment";
    String DELETE_APPOINTMENT = "deleteAppointment";
    String UPDATE_APPOINTMENT = "updateAppointment";

    CompletableFuture<Iterable<Appointment>> getAppointments();
    CompletableFuture<String> addAppointment(Long petId, Long vetId, String type, String date);
    CompletableFuture<String> deleteAppointment(Long id);
    CompletableFuture<String> updateAppointment(Long id, Long petId, Long vetId, String type, String date);
}
