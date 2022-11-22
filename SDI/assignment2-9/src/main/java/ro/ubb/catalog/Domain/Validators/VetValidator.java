package ro.ubb.catalog.Domain.Validators;


import ro.ubb.catalog.Domain.Vet;

public class VetValidator implements Validator<Vet> {
    @Override
    public void validate(Vet entity) throws ValidatorException, IllegalArgumentException{
        if(entity == null){
            throw new IllegalArgumentException("Entity is null");
        }
        if(entity.getId() < 0)
            throw new ValidatorException("Invalid vet id");
        if (entity.getSalary() < 0)
            throw new ValidatorException("Invalid salary");

        if (entity.getRating() < 0 || entity.getRating() > 10)
            throw new ValidatorException("Invalid rating");
        
    }
}
