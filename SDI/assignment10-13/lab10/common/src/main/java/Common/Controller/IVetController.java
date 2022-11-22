package Common.Controller;

import Common.Model.Domain.Appointment;
import Common.Model.Domain.Pet;
import Common.Model.Domain.Vet;

import java.util.concurrent.CompletableFuture;

public interface IVetController extends IBaseController {
    String GET_VETS = "getVets";
    String GET_VET_PATIENTS = "getVetPatients";
    String GET_VET_APPOINTMENTS = "getVetAppointments";
    String ADD_VET = "addVet";
    String DELETE_VET = "deleteVet";
    String UPDATE_VET = "updateVet";

    CompletableFuture<Iterable<Vet>> getVets();
    CompletableFuture<Iterable<Pet>> getVetPatients(Long id);
    CompletableFuture<Iterable<Appointment>> getVetAppointments(Long id);
    CompletableFuture<String> addVet(String firstName, String lastName, String email, String phoneNumber, String dateOfBirth, int salary ,int rating);
    CompletableFuture<String> deleteVet(Long id);
    CompletableFuture<String> updateVet(Long id, String firstName, String lastName, String email, String phoneNumber, String dateOfBirth, int salary ,int rating);
}
