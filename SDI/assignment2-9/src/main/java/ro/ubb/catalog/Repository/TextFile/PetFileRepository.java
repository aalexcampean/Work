package ro.ubb.catalog.Repository.TextFile;

import ro.ubb.catalog.Domain.Pet;
import ro.ubb.catalog.Domain.Validators.Validator;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Repository.InMemory.InMemoryRepository;

import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;

/**
 * @author radu.
 */
public class PetFileRepository extends InMemoryRepository<Long, Pet> {
    private String fileName;

    public PetFileRepository(Validator<Pet> validator, String fileName) {
        super(validator);
        this.fileName = fileName;

        loadData();
    }
    public Validator<Pet> getValidator() {
        return super.getValidator();
    }

    private void loadData() {
        Path path = Paths.get(fileName);

        try {
            Files.lines(path).forEach(line -> {
                List<String> items = Arrays.asList(line.split(","));

                Long id = Long.valueOf(items.get(0));
                String species = items.get(1);
                String breed = items.get((2));
                String petName = items.get((3));
                int personId = Integer.parseInt(items.get(4));

                Pet pet = new Pet(species, breed, petName, personId);
                pet.setId(id);

                try {
                    super.save(pet);
                } catch (ValidatorException e) {
                    e.printStackTrace();
                }
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    @Override
    public Optional<Pet> save(Pet entity) throws ValidatorException {
        Optional<Pet> optional = super.save(entity);
        if (optional.isPresent()) {
            return optional;
        }
        saveToFile(entity);
        return Optional.empty();
    }

    private void saveToFile(Pet entity) {
        Path path = Paths.get(fileName);

        try (BufferedWriter bufferedWriter = Files.newBufferedWriter(path, StandardOpenOption.APPEND)) {
            bufferedWriter.write(
                    entity.getId() + "," + entity.getSpecies() + "," + entity.getBreed() + "," + entity.getPetName() + "," + entity.getPersonId());
            bufferedWriter.newLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
