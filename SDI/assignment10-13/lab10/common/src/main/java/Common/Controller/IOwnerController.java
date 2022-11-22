package Common.Controller;

import Common.Model.Domain.Owner;
import Common.Model.Domain.Pet;

import java.util.concurrent.CompletableFuture;

public interface IOwnerController extends IBaseController {
    String GET_OWNERS = "getOwners";
    String GET_OWNER_PETS = "getOwnerPets";
    String ADD_OWNER = "addOwner";
    String DELETE_OWNER = "deleteOwner";
    String UPDATE_OWNER = "updateOwner";

    CompletableFuture<Iterable<Owner>> getOwners();
    CompletableFuture<Iterable<Pet>> getOwnerPets(Long id);
    CompletableFuture<String> addOwner(String firstName, String lastName, String email, String phoneNumber, String dateOfBirth);
    CompletableFuture<String> deleteOwner(Long id);
    CompletableFuture<String> updateOwner(Long id, String firstName, String lastName, String email, String phoneNumber, String dateOfBirth);
}
