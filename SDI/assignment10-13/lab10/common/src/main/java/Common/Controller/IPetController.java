package Common.Controller;

import Common.Model.Domain.Appointment;
import Common.Model.Domain.Owner;
import Common.Model.Domain.Pet;

import java.util.concurrent.CompletableFuture;

public interface IPetController extends IBaseController {
    String GET_PETS = "getPets";
    String GET_PET_OWNER = "getPetOwner";
    String GET_PET_APPOINTMENTS = "getPetAppointments";
    String ADD_PET = "addPet";
    String DELETE_PET = "deletePet";
    String UPDATE_PET = "updatePet";

    CompletableFuture<Iterable<Pet>> getPets();
    CompletableFuture<Owner> getPetOwner(Long id);
    CompletableFuture<Iterable<Appointment>> getPetAppointments(Long id);
    CompletableFuture<String> addPet(String species, String breed, String name, String dateOfEnrolment, long personId);
    CompletableFuture<String> deletePet(Long id);
    CompletableFuture<String> updatePet(Long id, String species, String breed, String name, String dateOfEnrolment, long personId);
}
