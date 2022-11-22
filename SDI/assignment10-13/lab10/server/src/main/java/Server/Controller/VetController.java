package Server.Controller;

import Common.Controller.IVetController;
import Common.Model.Domain.Appointment;
import Common.Model.Domain.Pet;
import Common.Model.Domain.Vet;
import Common.Request.Request;
import Server.Service.VetService;
import Server.TCP.TCPConnection;

import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

public class VetController implements IVetController {
    private TCPConnection tcpConnection;
    private ExecutorService executorService;
    private VetService vetService;

    public VetController(TCPConnection tcpConnection, ExecutorService executorService, VetService vetService) {
        this.tcpConnection = tcpConnection;
        this.executorService = executorService;
        this.vetService = vetService;
        addRequestHandlers();
    }

    @Override
    public void addRequestHandlers() {
        tcpConnection.addHandler(GET_VETS, request -> {
            try {
                return new Request(Request.OK,
                        StreamSupport.stream(getVets().get().spliterator(), false)
                                .map(Vet::encode)
                                .collect(Collectors.joining("!")));
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });

        tcpConnection.addHandler(GET_VET_PATIENTS, request -> {
            try {
                Long id = Long.parseLong(request.getBody());
                return new Request(Request.OK,
                        StreamSupport.stream(getVetPatients(id).get().spliterator(), false)
                                .map(Pet::encode)
                                .collect(Collectors.joining("!")));
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });

        tcpConnection.addHandler(GET_VET_APPOINTMENTS, request -> {
            try {
                Long id = Long.parseLong(request.getBody());
                return new Request(Request.OK,
                        StreamSupport.stream(getVetAppointments(id).get().spliterator(), false)
                                .map(Appointment::encode)
                                .collect(Collectors.joining("!")));
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });

        tcpConnection.addHandler(ADD_VET, request -> {
            try {
                List<String> tokens = Stream.of(request.getBody().trim().split("\\s*,\\s*")).toList();
                String firstName = tokens.get(0);
                String lastName = tokens.get(1);
                String email = tokens.get(2);
                String phoneNumber = tokens.get(3);
                String dateOfBirth = tokens.get(4);
                Integer salary = Integer.parseInt(tokens.get(5));
                Integer rating = Integer.parseInt(tokens.get(6));

                String message = addVet(firstName, lastName, email, phoneNumber, dateOfBirth, salary, rating).get();
                return new Request(Request.OK, message);

            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });

        tcpConnection.addHandler(DELETE_VET, request -> {
            try {
                Long id = Long.parseLong(request.getBody());

                String message = deleteVet(id).get();
                return new Request(Request.OK, message);

            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });

        tcpConnection.addHandler(UPDATE_VET, request -> {
            try {
                List<String> tokens = Stream.of(request.getBody().trim().split("\\s*,\\s*")).toList();
                Long id = Long.parseLong(tokens.get(0));
                String firstName = tokens.get(1);
                String lastName = tokens.get(2);
                String email = tokens.get(3);
                String phoneNumber = tokens.get(4);
                String dateOfBirth = tokens.get(5);
                Integer salary = Integer.parseInt(tokens.get(6));
                Integer rating = Integer.parseInt(tokens.get(7));

                String message = updateVet(id, firstName, lastName, email, phoneNumber, dateOfBirth, salary, rating).get();
                return new Request(Request.OK, message);

            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });
    }

    @Override
    public CompletableFuture<Iterable<Vet>> getVets() {
        return CompletableFuture.supplyAsync(vetService::getVets, executorService);
    }

    @Override
    public CompletableFuture<Iterable<Pet>> getVetPatients(Long id) {
        return CompletableFuture.supplyAsync(() -> vetService.getVetPatients(id), executorService);
    }

    @Override
    public CompletableFuture<Iterable<Appointment>> getVetAppointments(Long id) {
        return CompletableFuture.supplyAsync(() -> vetService.getVetAppointments(id), executorService);
    }

    @Override
    public CompletableFuture<String> addVet(String firstName, String lastName, String email, String phoneNumber, String dateOfBirth, int salary, int rating) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                vetService.addVet(firstName, lastName, email, phoneNumber, dateOfBirth, salary, rating);
                return "Vet added successfully";
            } catch (Exception exception) {
                return exception.getMessage();
            }
        }, executorService);
    }

    @Override
    public CompletableFuture<String> deleteVet(Long id) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                vetService.deleteVet(id);
                return "Vet deleted successfully";
            } catch (Exception exception) {
                return exception.getMessage();
            }
        }, executorService);
    }

    @Override
    public CompletableFuture<String> updateVet(Long id, String firstName, String lastName, String email, String phoneNumber, String dateOfBirth, int salary, int rating) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                vetService.updateVet(id, firstName, lastName, email, phoneNumber, dateOfBirth, salary, rating);
                return "Vet updated successfully";
            } catch (Exception exception) {
                return exception.getMessage();
            }
        }, executorService);
    }
}
