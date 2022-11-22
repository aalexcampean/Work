package Common.Model.Validators;

import Common.Model.Domain.Pet;

import java.util.Objects;

public class PetValidator implements IValidator<Pet> {
    @Override
    public void validate(Pet pet) throws ValidatorException {
        if (pet == null)
            throw new IllegalArgumentException("Pet is null");

        if (pet.getId() < 0)
            throw new ValidatorException("Invalid pet id");

        if (Objects.equals(pet.getSpecies(), ""))
            throw new ValidatorException("Invalid pet species");

        if (Objects.equals(pet.getBreed(), ""))
            throw new ValidatorException("Invalid pet breed");

        if (Objects.equals(pet.getName(), ""))
            throw new ValidatorException("Invalid pet name");

        char firstLetter = pet.getName().charAt(0);
        if(!Character.isUpperCase(firstLetter))
            throw new ValidatorException("Pet name should start with Upper Case letter!");

        if (Objects.equals(pet.getDateOfEnrolment(), ""))
            throw new ValidatorException("Invalid pet date of enrolment");

        if (pet.getPersonId() < 0)
            throw new ValidatorException("Invalid pet person id");
    }
}
