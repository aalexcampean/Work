package ro.ubb.catalog.Domain.Validators;

import ro.ubb.catalog.Domain.VetContract;

public class VetContractValidator implements Validator<VetContract> {
    @Override
    public void validate(VetContract entity) throws ValidatorException, IllegalArgumentException {
        if(entity == null)
            throw new IllegalArgumentException("Null entity!");
        if (entity.getId() < 0)
            throw new ValidatorException("Invalid Vet Contract ID!");
        if (entity.getVetID() < 0)
            throw new ValidatorException("Invalid Vet Vet ID!");
        if (entity.getClinicID() < 0)
            throw new ValidatorException("Invalid Vet Clinic ID!");
    }
}
