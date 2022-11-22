package ro.ubb.catalog.Service;

import ro.ubb.catalog.Domain.Validators.Validator;
import ro.ubb.catalog.Domain.VetContract;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Repository.Repository;

import java.time.LocalDate;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class VetContractService {
    private Repository<Long, VetContract> repository;
    private Validator<VetContract> validator;


    public VetContractService(Repository<Long, VetContract> repo, Validator<VetContract> validator){
        this.repository=repo;
        this.validator=validator;
    }

    public void addVetContract(VetContract v) throws ValidatorException, IllegalArgumentException {
        this.validator.validate(v);
        this.repository.save(v);
    }

    public Optional<VetContract> deleteVetContract(Long id) throws IllegalArgumentException {
        if (id == null) {
            throw new IllegalArgumentException("Null Vet Contract ID");
        }
        return this.repository.delete(id);
    }

    public Optional<VetContract> updateVetContract(VetContract v) throws ValidatorException, IllegalArgumentException{
        this.validator.validate(v);
        return this.repository.update(v);
    }

    public Set<VetContract> getAllVetContracts(){
        Iterable<VetContract> ecs=this.repository.findAll();
        return StreamSupport.stream(ecs.spliterator(), false)
                .collect(Collectors.toSet());
    }

    public Set<VetContract> filterVetContracts(String str) {
        Iterable<VetContract> vcs = repository.findAll();
        Set<VetContract> filteredVCs= new HashSet<>();
        vcs.forEach(filteredVCs::add);
        filteredVCs.removeIf(EmployeeContract -> {
            return EmployeeContract.getContractDate().compareTo(LocalDate.parse(str)) > 0;
        });

        return filteredVCs;
    }
}