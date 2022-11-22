package Client.Controller;

import Client.TCP.TCPConnection;
import Common.Controller.IOwnerController;
import Common.Model.Domain.Owner;
import Common.Model.Domain.Pet;
import Common.Request.Request;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutorService;

public class OwnerController implements IOwnerController {
    private TCPConnection tcpConnection;
    private ExecutorService executorService;

    public OwnerController(TCPConnection tcpConnection, ExecutorService executorService) {
        this.tcpConnection = tcpConnection;
        this.executorService = executorService;
    }

    @Override
    public void addRequestHandlers() {
    }

    @Override
    public CompletableFuture<Iterable<Owner>> getOwners() {
        return CompletableFuture.supplyAsync(() -> {
            Request request = new Request(IOwnerController.GET_OWNERS, "");
            Request response = tcpConnection.sendAndReceive(request);

            String result = response.getBody();
            List<Owner> owners = new ArrayList<>();
            Arrays.stream(result.split("!")).map(Owner::decode)
                    .forEach(owners::add);
            return owners;
        }, executorService);
    }

    @Override
    public CompletableFuture<Iterable<Pet>> getOwnerPets(Long id) {
        return CompletableFuture.supplyAsync(() -> {
            Request request = new Request(IOwnerController.GET_OWNER_PETS, String.valueOf(id));
            Request response = tcpConnection.sendAndReceive(request);

            String result = response.getBody();
            List<Pet> pets = new ArrayList<>();
            Arrays.stream(result.split("!")).map(Pet::decode)
                    .forEach(pets::add);
            return pets;
        }, executorService);
    }

    @Override
    public CompletableFuture<String> addOwner(String firstName, String lastName, String email, String phoneNumber, String dateOfBirth) {
        return CompletableFuture.supplyAsync(() -> {
            String body = firstName + "," + lastName + "," + email + "," + phoneNumber + "," + dateOfBirth;
            Request request = new Request(IOwnerController.ADD_OWNER, body);
            return tcpConnection.sendAndReceive(request).getBody();
        }, executorService);
    }

    @Override
    public CompletableFuture<String> deleteOwner(Long id) {
        return CompletableFuture.supplyAsync(() -> {
            Request request = new Request(IOwnerController.DELETE_OWNER, String.valueOf(id));
            return tcpConnection.sendAndReceive(request).getBody();
        }, executorService);
    }

    @Override
    public CompletableFuture<String> updateOwner(Long id, String firstName, String lastName, String email, String phoneNumber, String dateOfBirth) {
        return CompletableFuture.supplyAsync(() -> {
            String body = id + "," + firstName + "," + lastName + "," + email + "," + phoneNumber + "," + dateOfBirth;
            Request request = new Request(IOwnerController.UPDATE_OWNER, body);
            return tcpConnection.sendAndReceive(request).getBody();
        }, executorService);
    }
}
