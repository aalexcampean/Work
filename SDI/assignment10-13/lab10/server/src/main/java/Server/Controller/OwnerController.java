package Server.Controller;

import Common.Controller.IOwnerController;
import Common.Model.Domain.Owner;
import Common.Model.Domain.Pet;
import Common.Request.Request;
import Server.Service.OwnerService;
import Server.TCP.TCPConnection;

import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

public class OwnerController implements IOwnerController {
    private TCPConnection tcpConnection;
    private ExecutorService executorService;
    private OwnerService ownerService;

    public OwnerController(TCPConnection tcpConnection, ExecutorService executorService, OwnerService ownerService) {
        this.tcpConnection = tcpConnection;
        this.executorService = executorService;
        this.ownerService = ownerService;
        addRequestHandlers();
    }

    @Override
    public void addRequestHandlers() {
        tcpConnection.addHandler(GET_OWNERS, request -> {
            try {
                return new Request(Request.OK,
                        StreamSupport.stream(getOwners().get().spliterator(), false)
                                .map(Owner::encode)
                                .collect(Collectors.joining("!")));
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });

        tcpConnection.addHandler(GET_OWNER_PETS, request -> {
            try {
                Long id = Long.parseLong(request.getBody());
                return new Request(Request.OK,
                        StreamSupport.stream(getOwnerPets(id).get().spliterator(), false)
                                .map(Pet::encode)
                                .collect(Collectors.joining("!")));
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });

        tcpConnection.addHandler(ADD_OWNER, request -> {
            try {
                List<String> tokens = Stream.of(request.getBody().trim().split("\\s*,\\s*")).toList();
                String firstName = tokens.get(0);
                String lastName = tokens.get(1);
                String email = tokens.get(2);
                String phoneNumber = tokens.get(3);
                String dateOfBirth = tokens.get(4);

                String message = addOwner(firstName, lastName, email, phoneNumber, dateOfBirth).get();
                return new Request(Request.OK, message);

            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });

        tcpConnection.addHandler(DELETE_OWNER, request -> {
            try {
                Long id = Long.parseLong(request.getBody());

                String message = deleteOwner(id).get();
                return new Request(Request.OK, message);

            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });

        tcpConnection.addHandler(UPDATE_OWNER, request -> {
            try {
                List<String> tokens = Stream.of(request.getBody().trim().split("\\s*,\\s*")).toList();
                Long id = Long.parseLong(tokens.get(0));
                String firstName = tokens.get(1);
                String lastName = tokens.get(2);
                String email = tokens.get(3);
                String phoneNumber = tokens.get(4);
                String dateOfBirth = tokens.get(5);

                String message = updateOwner(id, firstName, lastName, email, phoneNumber, dateOfBirth).get();
                return new Request(Request.OK, message);

            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });
    }

    @Override
    public CompletableFuture<Iterable<Owner>> getOwners() {
        return CompletableFuture.supplyAsync(ownerService::getOwners, executorService);
    }

    @Override
    public CompletableFuture<Iterable<Pet>> getOwnerPets(Long id) {
        return CompletableFuture.supplyAsync(() -> ownerService.getOwnerPets(id), executorService);
    }

    @Override
    public CompletableFuture<String> addOwner(String firstName, String lastName, String email, String phoneNumber, String dateOfBirth) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                ownerService.addOwner(firstName, lastName, email, phoneNumber, dateOfBirth);
                return "Owner added successfully";
            } catch (Exception exception) {
                return exception.getMessage();
            }
        }, executorService);
    }

    @Override
    public CompletableFuture<String> deleteOwner(Long id) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                ownerService.deleteOwner(id);
                return "Owner deleted successfully";
            } catch (Exception exception) {
                return exception.getMessage();
            }
        }, executorService);
    }

    @Override
    public CompletableFuture<String> updateOwner(Long id, String firstName, String lastName, String email, String phoneNumber, String dateOfBirth) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                ownerService.updateOwner(id, firstName, lastName, email, phoneNumber, dateOfBirth);
                return "Owner updated successfully";
            } catch (Exception exception) {
                return exception.getMessage();
            }
        }, executorService);
    }
}
