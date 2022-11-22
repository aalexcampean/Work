package ro.ubb.catalog.Domain.Validators;


import ro.ubb.catalog.Domain.EmployeeContract;

public class EmployeeContractValidator implements Validator<EmployeeContract> {
    @Override
    public void validate(EmployeeContract entity) throws ValidatorException {
        if(entity.getId() < 0)
            throw new ValidatorException("Invalid EmployeeContractID");
        if (entity.getEmployeeID() < 0)
            throw new ValidatorException("Invalid EmployeeID");
        if (entity.getClinicID() < 0)
            throw new ValidatorException("Invalid ClinicID");
        //Don't see any way to validate the date, unless we just make up some rules.
    }
}