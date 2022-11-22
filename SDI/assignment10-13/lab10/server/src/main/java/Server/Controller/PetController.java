package Server.Controller;

import Common.Controller.IPetController;
import Common.Model.Domain.Appointment;
import Common.Model.Domain.Owner;
import Common.Model.Domain.Pet;
import Common.Request.Request;
import Server.Service.PetService;
import Server.TCP.TCPConnection;

import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

public class PetController implements IPetController {
    private TCPConnection tcpConnection;
    private ExecutorService executorService;
    private PetService petService;

    public PetController(TCPConnection tcpConnection, ExecutorService executorService, PetService petService) {
        this.tcpConnection = tcpConnection;
        this.executorService = executorService;
        this.petService = petService;
        addRequestHandlers();
    }

    @Override
    public void addRequestHandlers() {
        tcpConnection.addHandler(GET_PETS, request -> {
            try {
                return new Request(Request.OK,
                        StreamSupport.stream(getPets().get().spliterator(), false)
                                .map(Pet::encode)
                                .collect(Collectors.joining("!")));
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });

        tcpConnection.addHandler(GET_PET_OWNER, request -> {
            try {
                Long id = Long.parseLong(request.getBody());
                return new Request(Request.OK, getPetOwner(id).get().encode());
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });

        tcpConnection.addHandler(GET_PET_APPOINTMENTS, request -> {
            try {
                Long id = Long.parseLong(request.getBody());
                return new Request(Request.OK,
                        StreamSupport.stream(getPetAppointments(id).get().spliterator(), false)
                                .map(Appointment::encode)
                                .collect(Collectors.joining("!")));
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });

        tcpConnection.addHandler(ADD_PET, request -> {
            try {
                List<String> tokens = Stream.of(request.getBody().trim().split("\\s*,\\s*")).toList();
                String species = tokens.get(0);
                String breed = tokens.get(1);
                String name = tokens.get(2);
                String dateOfEnrolment = tokens.get(3);
                Long personId = Long.parseLong(tokens.get(4));

                String message = addPet(species, breed, name, dateOfEnrolment, personId).get();
                return new Request(Request.OK, message);

            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });

        tcpConnection.addHandler(DELETE_PET, request -> {
            try {
                Long id = Long.parseLong(request.getBody());

                String message = deletePet(id).get();
                return new Request(Request.OK, message);

            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });

        tcpConnection.addHandler(UPDATE_PET, request -> {
            try {
                List<String> tokens = Stream.of(request.getBody().trim().split("\\s*,\\s*")).toList();
                Long id = Long.parseLong(tokens.get(0));
                String species = tokens.get(1);
                String breed = tokens.get(2);
                String name = tokens.get(3);
                String dateOfEnrolment = tokens.get(4);
                Long personId = Long.parseLong(tokens.get(5));

                String message = updatePet(id, species, breed, name, dateOfEnrolment, personId).get();
                return new Request(Request.OK, message);

            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
                return new Request(Request.ERROR, e.getMessage());
            }
        });
    }

    @Override
    public CompletableFuture<Iterable<Pet>> getPets() {
        return CompletableFuture.supplyAsync(petService::getPets, executorService);
    }

    @Override
    public CompletableFuture<Owner> getPetOwner(Long id) {
        return CompletableFuture.supplyAsync(() -> petService.getPetOwner(id), executorService);
    }

    @Override
    public CompletableFuture<Iterable<Appointment>> getPetAppointments(Long id) {
        return CompletableFuture.supplyAsync(() -> petService.getPetAppointments(id), executorService);
    }

    @Override
    public CompletableFuture<String> addPet(String species, String breed, String name, String dateOfEnrolment, long personId) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                petService.addPet(species, breed, name, dateOfEnrolment, personId);
                return "Pet added successfully";
            } catch (Exception exception) {
                return exception.getMessage();
            }
        }, executorService);
    }

    @Override
    public CompletableFuture<String> deletePet(Long id) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                petService.deletePet(id);
                return "Pet deleted successfully";
            } catch (Exception exception) {
                return exception.getMessage();
            }
        }, executorService);
    }

    @Override
    public CompletableFuture<String> updatePet(Long id, String species, String breed, String name, String dateOfEnrolment, long personId) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                petService.updatePet(id, species, breed, name, dateOfEnrolment, personId);
                return "Pet updated successfully";
            } catch (Exception exception) {
                return exception.getMessage();
            }
        }, executorService);
    }
}
