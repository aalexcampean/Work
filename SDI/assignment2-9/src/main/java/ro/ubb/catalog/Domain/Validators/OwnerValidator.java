package ro.ubb.catalog.Domain.Validators;

import ro.ubb.catalog.Domain.Owner;

public class OwnerValidator implements Validator<Owner>{
    @Override
    public void validate(Owner entity) throws ValidatorException{
        if(entity.getId() < 0)
            throw new ValidatorException("Invalid OwnerID");
    }
}
