package ro.ubb.catalog.Service;

import ro.ubb.catalog.Domain.Employee;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Repository.Repository;

import java.util.HashSet;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class EmployeeService {

    private Repository<Long, Employee> repository;

    public EmployeeService(Repository<Long, Employee> repository){
        this.repository = repository;
    }

    public void addEmployee(Employee employee) throws ValidatorException {
        repository.save(employee);
    }

    public Set<Employee> getAllEmployees(){
        Iterable<Employee> employees = repository.findAll();
        return StreamSupport.stream(employees.spliterator(), false).collect(Collectors.toSet());
    }

    public Set<Employee> filterEmployeesByLastName(String s){
        Iterable<Employee> employees = repository.findAll();

        Set<Employee> filteredEmployees = new HashSet<>();
        employees.forEach(filteredEmployees::add);
        filteredEmployees.removeIf(employee -> !employee.getLastName().contains(s));

        return filteredEmployees;
    }

    public void deleteEmployee(Long id){
        repository.delete(id);
    }

    public void updateEmployee(Employee employee){
        repository.update(employee);
    }
}
