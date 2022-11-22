package ro.ubb.catalog.Domain.Validators;

import ro.ubb.catalog.Domain.Pet;

/**
 * @author olivia.
 */
public class PetValidator implements Validator<Pet> {
    @Override
    public void validate(Pet entity) throws ValidatorException {
        if(entity.getId() < 0)
            throw new ValidatorException("Pet ID cannot be a negative number!");
        if(entity.getPersonId() < 0 )
            throw new ValidatorException("Person ID cannot be a negative number!");

        

        char firstLetter = entity.getPetName().charAt(0);
        if(!Character.isUpperCase(firstLetter))
            throw new ValidatorException("Pet name should start with an Upper Case letter!");
    }
}
