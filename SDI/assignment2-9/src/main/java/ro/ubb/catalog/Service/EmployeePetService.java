package ro.ubb.catalog.Service;

import ro.ubb.catalog.Domain.EmployeePet;
import ro.ubb.catalog.Domain.Validators.EmployeePetValidator;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Repository.Repository;

import java.util.HashSet;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class EmployeePetService {
    private Repository<Long, EmployeePet> repository;
    private EmployeePetValidator employeePetValidator;

    public EmployeePetService(Repository<Long, EmployeePet> repository, EmployeePetValidator employeePetValidator) {
        this.repository = repository;
        this.employeePetValidator = employeePetValidator;
    }

    /**
     * Add an employee-pet
     * @param employeePet - the employee-pet to be added
     * @throws ValidatorException - throw exception in case the employee-pet is not valid
     */
    public void addEmployeePet(EmployeePet employeePet) throws ValidatorException {
        employeePetValidator.validate(employeePet);
        this.repository.save(employeePet);
    }

    /**
     * Delete an employee-pet
     * @param employeePetId Long - the id of the surgery to be deleted
     */
    public void deleteEmployeePet(Long employeePetId) {
        repository.delete(employeePetId);
    }

    /**
     * Update an employee-pet
     * @param employeePet - the employee-pet with the new attributes
     */
    public void updateEmployeePet(EmployeePet employeePet) {
        repository.update(employeePet);
    }

    /**
     * Returns all the employee-pets
     * @return all employee-pets
     */
    public Set<EmployeePet> getAllEmployeePets(){
        Iterable<EmployeePet> employeePets = this.repository.findAll();
        return StreamSupport.stream(employeePets.spliterator(), false).collect(Collectors.toSet());
    }

    /**
     * Returns all the employee-pets that have the given type of action.
     * @param s String - the type of action for filtering
     * @return filtered employee-pet
     */
    public Set<EmployeePet> filterEmployeePetsByType(String s) {
        Iterable<EmployeePet> employeePets = repository.findAll();
        Set<EmployeePet> filteredEmployeePets = new HashSet<>();
        employeePets.forEach(filteredEmployeePets::add);
        filteredEmployeePets.removeIf(employeePet -> !employeePet.getTypeOfAction().contains(s));

        return filteredEmployeePets;
    }
}
