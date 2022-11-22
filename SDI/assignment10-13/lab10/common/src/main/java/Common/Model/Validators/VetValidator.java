package Common.Model.Validators;

import Common.Model.Domain.Vet;

import java.util.Objects;

public class VetValidator implements IValidator<Vet> {
    @Override
    public void validate(Vet vet) throws ValidatorException, IllegalArgumentException {
        if (vet == null)
            throw new IllegalArgumentException("Vet is null");

        if (vet.getId() < 0)
            throw new ValidatorException("Invalid vet id");

        if (Objects.equals(vet.getFirstName(), ""))
            throw new ValidatorException("Invalid vet first name");

        char firstLetter = vet.getFirstName().charAt(0);
        if(!Character.isUpperCase(firstLetter))
            throw new ValidatorException("Vet first name should start with Upper Case letter!");

        if (Objects.equals(vet.getLastName(), ""))
            throw new ValidatorException("Invalid vet last name");

        firstLetter = vet.getLastName().charAt(0);
        if(!Character.isUpperCase(firstLetter))
            throw new ValidatorException("Vet last name should start with Upper Case letter!");

        if (Objects.equals(vet.getEmail(), ""))
            throw new ValidatorException("Invalid vet email");

        if (Objects.equals(vet.getPhoneNumber(), ""))
            throw new ValidatorException("Invalid vet phone number");

        if (Objects.equals(vet.getDateOfBirth(), ""))
            throw new ValidatorException("Invalid vet date of birth");

        if (vet.getSalary() < 0)
            throw new ValidatorException("Invalid salary");

        if (vet.getRating() < 0 || vet.getRating() > 10)
            throw new ValidatorException("Invalid rating");
    }
}
