package Server.Controller;

import Common.Controller.IAppointmentController;
import Common.Model.Domain.Appointment;
import Common.Request.Request;
import Server.Service.AppointmentService;
import Server.TCP.TCPConnection;

import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

public class AppointmentController implements IAppointmentController {
    private TCPConnection tcpConnection;
    private ExecutorService executorService;
    private AppointmentService appointmentService;

    public AppointmentController(TCPConnection tcpConnection, ExecutorService executorService, AppointmentService appointmentService) {
        this.tcpConnection = tcpConnection;
        this.executorService = executorService;
        this.appointmentService = appointmentService;
        addRequestHandlers();
    }

    @Override
    public void addRequestHandlers() {
        tcpConnection.addHandler(GET_APPOINTMENTS, request -> {
            try {
                return new Request(Request.OK,
                        StreamSupport.stream(getAppointments().get().spliterator(), false)
                                .map(Appointment::encode)
                                .collect(Collectors.joining("!")));
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });

        tcpConnection.addHandler(ADD_APPOINTMENT, request -> {
            try {
                List<String> tokens = Stream.of(request.getBody().trim().split("\\s*,\\s*")).toList();
                Long petId = Long.parseLong(tokens.get(0));
                Long vetId = Long.parseLong(tokens.get(1));
                String type = tokens.get(2);
                String date = tokens.get(3);

                String message = addAppointment(petId, vetId, type, date).get();
                return new Request(Request.OK, message);

            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });

        tcpConnection.addHandler(DELETE_APPOINTMENT, request -> {
            try {
                Long id = Long.parseLong(request.getBody());

                String message = deleteAppointment(id).get();
                return new Request(Request.OK, message);

            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });

        tcpConnection.addHandler(UPDATE_APPOINTMENT, request -> {
            try {
                List<String> tokens = Stream.of(request.getBody().trim().split("\\s*,\\s*")).toList();
                Long id = Long.parseLong(tokens.get(0));
                Long petId = Long.parseLong(tokens.get(1));
                Long vetId = Long.parseLong(tokens.get(2));
                String type = tokens.get(3);
                String date = tokens.get(4);

                String message = updateAppointment(id, petId, vetId, type, date).get();
                return new Request(Request.OK, message);

            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });
    }

    @Override
    public CompletableFuture<Iterable<Appointment>> getAppointments() {
        return CompletableFuture.supplyAsync(appointmentService::getAppointments, executorService);
    }

    @Override
    public CompletableFuture<String> addAppointment(Long petId, Long vetId, String type, String date) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                appointmentService.addAppointment(petId, vetId, type, date);
                return "Appointment added successfully";
            } catch (Exception exception) {
                return exception.getMessage();
            }
        }, executorService);
    }

    @Override
    public CompletableFuture<String> deleteAppointment(Long id) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                appointmentService.deleteAppointment(id);
                return "Appointment deleted successfully";
            } catch (Exception exception) {
                return exception.getMessage();
            }
        }, executorService);
    }

    @Override
    public CompletableFuture<String> updateAppointment(Long id, Long petId, Long vetId, String type, String date) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                appointmentService.updateAppointment(id, petId, vetId, type, date);
                return "Appointment updated successfully";
            } catch (Exception exception) {
                return exception.getMessage();
            }
        }, executorService);
    }
}
