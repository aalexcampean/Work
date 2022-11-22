package ro.ubb.catalog.Domain.Validators;

import ro.ubb.catalog.Domain.Surgery;

public class SurgeryValidator implements Validator<Surgery> {
    @Override
    public void validate(Surgery entity) throws ValidatorException {
        if(entity.getId() < 0)
            throw new ValidatorException("Invalid SurgeryID");
        if(entity.getPetId() < 0)
            throw new ValidatorException("Invalid PetID");
        if(entity.getVetId() < 0)
            throw new ValidatorException("Invalid VetID");
    }
}
