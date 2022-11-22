package ro.ubb.catalog.Domain.Validators;

import ro.ubb.catalog.Domain.EmployeePet;

public class EmployeePetValidator implements Validator<EmployeePet> {
    @Override
    public void validate(EmployeePet entity) throws ValidatorException {
        if(entity.getId() < 0)
            throw new ValidatorException("Invalid PetID");
    }
}
