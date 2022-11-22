package ro.ubb.catalog.Domain.Validators;

import ro.ubb.catalog.Domain.Employee;

public class EmployeeValidator implements Validator<Employee>{
    @Override
    public void validate(Employee entity) throws ValidatorException {
        if(entity.getId()<0){
            throw new ValidatorException("Invalid employee id");
        }

        if(entity.getSalary()<0){
            throw new ValidatorException("Invalid employee salary");
        }

        if(entity.getRating()<0){
            throw new ValidatorException("Invalid employee rating");
        }
    }
}
