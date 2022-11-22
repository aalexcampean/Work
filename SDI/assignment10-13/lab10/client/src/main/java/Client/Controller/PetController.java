package Client.Controller;

import Client.TCP.TCPConnection;
import Common.Controller.IPetController;
import Common.Model.Domain.Appointment;
import Common.Model.Domain.Owner;
import Common.Model.Domain.Pet;
import Common.Request.Request;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutorService;

public class PetController implements IPetController {
    private TCPConnection tcpConnection;
    private ExecutorService executorService;

    public PetController(TCPConnection tcpConnection, ExecutorService executorService) {
        this.tcpConnection = tcpConnection;
        this.executorService = executorService;
    }

    @Override
    public void addRequestHandlers() {
    }

    @Override
    public CompletableFuture<Iterable<Pet>> getPets() {
        return CompletableFuture.supplyAsync(() -> {
            Request request = new Request(IPetController.GET_PETS, "");
            Request response = tcpConnection.sendAndReceive(request);

            String result = response.getBody();
            List<Pet> employees = new ArrayList<>();
            Arrays.stream(result.split("!")).map(Pet::decode)
                    .forEach(employees::add);
            return employees;
        }, executorService);
    }

    @Override
    public CompletableFuture<Owner> getPetOwner(Long id) {
        return CompletableFuture.supplyAsync(() -> {
            Request request = new Request(IPetController.GET_PET_OWNER, String.valueOf(id));
            Request response = tcpConnection.sendAndReceive(request);

            String result = response.getBody();
            return Owner.decode(result);
        }, executorService);
    }

    @Override
    public CompletableFuture<Iterable<Appointment>> getPetAppointments(Long id) {
        return CompletableFuture.supplyAsync(() -> {
            Request request = new Request(IPetController.GET_PET_APPOINTMENTS, String.valueOf(id));
            Request response = tcpConnection.sendAndReceive(request);

            String result = response.getBody();
            List<Appointment> appointments = new ArrayList<>();
            Arrays.stream(result.split("!")).map(Appointment::decode)
                    .forEach(appointments::add);
            return appointments;
        }, executorService);
    }

    @Override
    public CompletableFuture<String> addPet(String species, String breed, String name, String dateOfEnrolment, long personId) {
        return CompletableFuture.supplyAsync(() -> {
            String body = species + "," + breed + "," + name + "," + dateOfEnrolment + "," + personId;
            Request request = new Request(IPetController.ADD_PET, body);
            return tcpConnection.sendAndReceive(request).getBody();
        }, executorService);
    }

    @Override
    public CompletableFuture<String> deletePet(Long id) {
        return CompletableFuture.supplyAsync(() -> {
            Request request = new Request(IPetController.DELETE_PET, String.valueOf(id));
            return tcpConnection.sendAndReceive(request).getBody();
        }, executorService);
    }

    @Override
    public CompletableFuture<String> updatePet(Long id, String species, String breed, String name, String dateOfEnrolment, long personId) {
        return CompletableFuture.supplyAsync(() -> {
            String body = id + "," + species + "," + breed + "," + name + "," + dateOfEnrolment + "," + personId;
            Request request = new Request(IPetController.UPDATE_PET, body);
            return tcpConnection.sendAndReceive(request).getBody();
        }, executorService);
    }
}
