package Client.Controller;

import Client.TCP.TCPConnection;
import Common.Controller.IVetController;
import Common.Model.Domain.Appointment;
import Common.Model.Domain.Pet;
import Common.Model.Domain.Vet;
import Common.Request.Request;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutorService;

public class VetController implements IVetController {
    private TCPConnection tcpConnection;
    private ExecutorService executorService;

    public VetController(TCPConnection tcpConnection, ExecutorService executorService) {
        this.tcpConnection = tcpConnection;
        this.executorService = executorService;
    }

    @Override
    public void addRequestHandlers() {
    }

    @Override
    public CompletableFuture<Iterable<Vet>> getVets() {
        return CompletableFuture.supplyAsync(() -> {
            Request request = new Request(IVetController.GET_VETS, "");
            Request response = tcpConnection.sendAndReceive(request);

            String result = response.getBody();
            List<Vet> vets = new ArrayList<>();
            Arrays.stream(result.split("!")).map(Vet::decode)
                    .forEach(vets::add);
            return vets;
        }, executorService);
    }

    @Override
    public CompletableFuture<Iterable<Pet>> getVetPatients(Long id) {
        return CompletableFuture.supplyAsync(() -> {
            Request request = new Request(IVetController.GET_VET_PATIENTS, String.valueOf(id));
            Request response = tcpConnection.sendAndReceive(request);

            String result = response.getBody();
            List<Pet> pets = new ArrayList<>();
            Arrays.stream(result.split("!")).map(Pet::decode)
                    .forEach(pets::add);
            return pets;
        }, executorService);
    }

    @Override
    public CompletableFuture<Iterable<Appointment>> getVetAppointments(Long id) {
        return CompletableFuture.supplyAsync(() -> {
            Request request = new Request(IVetController.GET_VET_APPOINTMENTS, String.valueOf(id));
            Request response = tcpConnection.sendAndReceive(request);

            String result = response.getBody();
            List<Appointment> appointments = new ArrayList<>();
            Arrays.stream(result.split("!")).map(Appointment::decode)
                    .forEach(appointments::add);
            return appointments;
        }, executorService);
    }

    @Override
    public CompletableFuture<String> addVet(String firstName, String lastName, String email, String phoneNumber, String dateOfBirth, int salary, int rating) {
        return CompletableFuture.supplyAsync(() -> {
            String body = firstName + "," + lastName + "," + email + "," + phoneNumber + "," + dateOfBirth + "," + salary + "," + rating;
            Request request = new Request(IVetController.ADD_VET, body);
            return tcpConnection.sendAndReceive(request).getBody();
        }, executorService);
    }

    @Override
    public CompletableFuture<String> deleteVet(Long id) {
        return CompletableFuture.supplyAsync(() -> {
            Request request = new Request(IVetController.DELETE_VET, String.valueOf(id));
            return tcpConnection.sendAndReceive(request).getBody();
        }, executorService);
    }

    @Override
    public CompletableFuture<String> updateVet(Long id, String firstName, String lastName, String email, String phoneNumber, String dateOfBirth, int salary, int rating) {
        return CompletableFuture.supplyAsync(() -> {
            String body = id + "," + firstName + "," + lastName + "," + email + "," + phoneNumber + "," + dateOfBirth + "," + salary + "," + rating;
            Request request = new Request(IVetController.UPDATE_VET, body);
            return tcpConnection.sendAndReceive(request).getBody();
        }, executorService);
    }
}
