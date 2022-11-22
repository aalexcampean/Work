package ro.ubb.catalog.Service;

import ro.ubb.catalog.Domain.Validators.Validator;
import ro.ubb.catalog.Domain.Validators.VetValidator;
import ro.ubb.catalog.Domain.Vet;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Repository.Repository;

import javax.xml.parsers.ParserConfigurationException;
import java.io.IOException;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class VetService {
    private Repository<Long, Vet> repository;
    private Validator<Vet> validator;

    public VetService(Repository<Long, Vet> repo, Validator<Vet> validator){
        this.repository=repo;
        this.validator = validator;
    }

    public void addVet(Vet v) throws ValidatorException, IllegalArgumentException {
        this.validator.validate(v);
        this.repository.save(v);
    }

    public Optional<Vet> deleteVet(Long id) throws IllegalArgumentException {
        if (id == null) {
            throw new IllegalArgumentException("Null vet ID");
        }
        return this.repository.delete(id);
    }

    public Optional<Vet> updateVet(Vet v) throws ValidatorException, IllegalArgumentException {
        this.validator.validate(v);
        return this.repository.update(v);
    }

    public Set<Vet> getAllVets(){
        Iterable<Vet> vets=this.repository.findAll();
        return StreamSupport.stream(vets.spliterator(), false).collect(Collectors.toSet());
    }
    public Set<Vet> filterVetsbyRating(int r) {
        Iterable<Vet> vets = repository.findAll();

        Set<Vet> filteredVets = new HashSet<>();
        vets.forEach(filteredVets::add);
        filteredVets.removeIf(vet -> vet.getRating() < r);

        return filteredVets;
    }
}
