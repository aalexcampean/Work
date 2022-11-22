package ro.ubb.catalog.Service;

import ro.ubb.catalog.Domain.Pet;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Repository.Repository;


import java.util.HashSet;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

/**
 * @author radu.
 */
public class PetService {
    //private Repository<Long, Pet> repository;
    private Repository<Long,Pet> repository;

    public PetService(Repository<Long, Pet> repository) {
        this.repository = repository;
    }

    public Repository<Long, Pet> getRepo(){
        return repository;
    }

    public void addPet(Pet student) throws ValidatorException {
        repository.save(student);
    }

    public void removePet(Long id) {
        repository.delete(id);
    }
    public void updatePet(Pet pet) {
        repository.update(pet);
    }

    public Set<Pet> getAllPets() {
        Iterable<Pet> pets = repository.findAll();
        return StreamSupport.stream(pets.spliterator(), false).collect(Collectors.toSet());
    }

    /**
     * Returns all pets whose name contain the given string.
     *
     * @param s String for filtering
     * @return filtered pets
     */
    public Set<Pet> filterPetsByName(String s) {
        Iterable<Pet> pets = repository.findAll();
        //version 1
//        Set<Student> filteredStudents = StreamSupport.stream(students.spliterator(), false)
//                .filter(student -> student.getName().contains(s)).collect(Collectors.toSet());

        //version 2
        Set<Pet> filteredStudents= new HashSet<>();
        pets.forEach(filteredStudents::add);
        filteredStudents.removeIf(pet -> !pet.getPetName().contains(s));

        return filteredStudents;
    }

}
