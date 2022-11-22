package ro.ubb.catalog.Service;

import ro.ubb.catalog.Domain.Owner;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Repository.Repository;

import java.util.HashSet;
import java.util.Optional;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class OwnerService {
    private Repository<Long, Owner> repository;

    public OwnerService(Repository<Long, Owner> repository) {
        this.repository = repository;
    }

    public void addOwner(Owner owner) throws ValidatorException {
        repository.save(owner);
    }

    public Set<Owner> getAllOwners(){
        Iterable<Owner> owners=repository.findAll();
        return StreamSupport.stream(owners.spliterator(), false).collect(Collectors.toSet());
    }

    public Set<Owner> filterOwnersByLastName(String s) {
        Iterable<Owner> owners = repository.findAll();

        Set<Owner> filteredOwners= new HashSet<>();
        owners.forEach(filteredOwners::add);
        filteredOwners.removeIf(owner -> !owner.getLastName().contains(s));

        return filteredOwners;
    }

    public Optional<Owner> deleteOwner(long id){
        return this.repository.delete(id);
    }

    public Optional<Owner> updateOwner(Owner owner){
        return this.repository.update(owner);
    }
}
