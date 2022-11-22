package Client.Controller;

import Client.TCP.TCPConnection;
import Common.Controller.IAppointmentController;
import Common.Model.Domain.Appointment;
import Common.Request.Request;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutorService;

public class AppointmentController implements IAppointmentController {
    private TCPConnection tcpConnection;
    private ExecutorService executorService;

    public AppointmentController(TCPConnection tcpConnection, ExecutorService executorService) {
        this.tcpConnection = tcpConnection;
        this.executorService = executorService;
    }

    @Override
    public void addRequestHandlers() {
    }

    @Override
    public CompletableFuture<Iterable<Appointment>> getAppointments() {
        return CompletableFuture.supplyAsync(() -> {
            Request request = new Request(IAppointmentController.GET_APPOINTMENTS, "");
            Request response = tcpConnection.sendAndReceive(request);

            String result = response.getBody();
            List<Appointment> appointments = new ArrayList<>();
            Arrays.stream(result.split("!")).map(Appointment::decode)
                    .forEach(appointments::add);
            return appointments;
        }, executorService);
    }

    @Override
    public CompletableFuture<String> addAppointment(Long petId, Long vetId, String type, String date) {
        return CompletableFuture.supplyAsync(() -> {
            String body = petId + "," + vetId + "," + type + "," + date;
            Request request = new Request(IAppointmentController.ADD_APPOINTMENT, body);
            return tcpConnection.sendAndReceive(request).getBody();
        }, executorService);
    }

    @Override
    public CompletableFuture<String> deleteAppointment(Long id) {
        return CompletableFuture.supplyAsync(() -> {
            Request request = new Request(IAppointmentController.DELETE_APPOINTMENT, String.valueOf(id));
            return tcpConnection.sendAndReceive(request).getBody();
        }, executorService);
    }

    @Override
    public CompletableFuture<String> updateAppointment(Long id, Long petId, Long vetId, String type, String date) {
        return CompletableFuture.supplyAsync(() -> {
            String body = id + "," + petId + "," + vetId + "," + type + "," + date;
            Request request = new Request(IAppointmentController.UPDATE_APPOINTMENT, body);
            return tcpConnection.sendAndReceive(request).getBody();
        }, executorService);
    }
}
