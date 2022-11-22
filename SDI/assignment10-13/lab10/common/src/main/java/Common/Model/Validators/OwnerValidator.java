package Common.Model.Validators;

import Common.Model.Domain.Owner;

import java.util.Objects;

public class OwnerValidator implements IValidator<Owner> {
    @Override
    public void validate(Owner owner) throws ValidatorException, IllegalArgumentException {
        if (owner == null)
            throw new IllegalArgumentException("Owner is null");

        if (owner.getId() < 0)
            throw new ValidatorException("Invalid owner id");

        if (Objects.equals(owner.getFirstName(), ""))
            throw new ValidatorException("Invalid owner first name");

        char firstLetter = owner.getFirstName().charAt(0);
        if(!Character.isUpperCase(firstLetter))
            throw new ValidatorException("Owner first name should start with Upper Case letter!");

        if (Objects.equals(owner.getLastName(), ""))
            throw new ValidatorException("Invalid owner last name");

        firstLetter = owner.getLastName().charAt(0);
        if(!Character.isUpperCase(firstLetter))
            throw new ValidatorException("Owner last name should start with Upper Case letter!");

        if (Objects.equals(owner.getEmail(), ""))
            throw new ValidatorException("Invalid owner email");

        if (Objects.equals(owner.getPhoneNumber(), ""))
            throw new ValidatorException("Invalid owner phone number");

        if (Objects.equals(owner.getDateOfBirth(), ""))
            throw new ValidatorException("Invalid owner date of birth");
    }
}
