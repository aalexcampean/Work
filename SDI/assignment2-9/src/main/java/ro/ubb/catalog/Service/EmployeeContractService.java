package ro.ubb.catalog.Service;

import ro.ubb.catalog.Domain.*;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Repository.Repository;

import java.time.LocalDate;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class EmployeeContractService {
    private Repository<Long, EmployeeContract> repository;

    public EmployeeContractService(Repository<Long, EmployeeContract> repo){
        this.repository=repo;
    }

    public void addEmployeeContract(EmployeeContract v) throws ValidatorException {
        this.repository.save(v);
    }

    public Set<EmployeeContract> getAllEmployeeContracts(){
        Iterable<EmployeeContract> ecs=this.repository.findAll();
        return StreamSupport.stream(ecs.spliterator(), false).collect(Collectors.toSet());
    }

    public Set<EmployeeContract> filterEmployeeContracts(String str) {
        Iterable<EmployeeContract> ecs = repository.findAll();
        Set<EmployeeContract> filteredECs= new HashSet<>();
        ecs.forEach(filteredECs::add);
        filteredECs.removeIf(EmployeeContract -> {
            if(EmployeeContract.getDate().compareTo(LocalDate.parse(str)) > 0) return true;
            else return false;});

        return filteredECs;
    }

    public Optional<EmployeeContract> deleteEmployeeContract(Long id){
        return repository.delete(id);
    }

    public Optional<EmployeeContract> updateEmployeeContract(EmployeeContract employee){
        return repository.update(employee);
    }


}