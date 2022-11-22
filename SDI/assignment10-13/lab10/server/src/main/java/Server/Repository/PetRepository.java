package Server.Repository;

import Common.Model.Domain.Pet;
import Common.Model.Validators.IValidator;
import Common.Model.Validators.ValidatorException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcOperations;

import java.util.Optional;

public class PetRepository implements IRepository<Long, Pet> {
    private final IValidator<Pet> validator;
    @Autowired
    private JdbcOperations jdbcOperations;

    public PetRepository(IValidator<Pet> validator) {
        this.validator = validator;
    }

    @Override
    public Optional<Pet> findOne(Long inputId) throws IllegalArgumentException {
        if (inputId == null)
            throw new IllegalArgumentException("Pet id is null");

        String cmd = "SELECT * FROM Pet WHERE ID = " + inputId;

        return jdbcOperations.query(cmd, (rs, i) -> {
            String species = rs.getString("Species");
            String breed = rs.getString("Breed");
            String name = rs.getString("Name");
            String dateOfEnrolment = rs.getString("DateOfEnrolment");
            Integer personId = rs.getInt("PersonId");

            return new Pet(inputId, species, breed, name, dateOfEnrolment, personId);
        }).stream().findFirst();
    }

    @Override
    public Iterable<Pet> findAll() {
        String cmd = "SELECT * FROM Pet";

        return jdbcOperations.query(cmd, (rs, i) -> {
            Long id = rs.getLong("Id");
            String species = rs.getString("Species");
            String breed = rs.getString("Breed");
            String name = rs.getString("Name");
            String dateOfEnrolment = rs.getString("DateOfEnrolment");
            Integer personId = rs.getInt("PersonId");

            return new Pet(id, species, breed, name, dateOfEnrolment, personId);
        });
    }

    @Override
    public Optional<Pet> save(Pet entity) throws IllegalArgumentException, ValidatorException {
        this.validator.validate(entity);

        String cmd = "INSERT INTO Pet (Species, Breed, Name, DateOfEnrolment, PersonId) VALUES (?, ?, ?, ?, ?)";

        try {
            Integer success = jdbcOperations.update(cmd, entity.getSpecies(), entity.getBreed(),
                    entity.getName(), entity.getDateOfEnrolment(), entity.getPersonId());
            if (success.equals(1)) {
                return Optional.empty();
            }
            return Optional.of(entity);
        } catch (Exception e) {
            return Optional.of(entity);
        }
    }

    @Override
    public Optional<Pet> delete(Long inputId) throws IllegalArgumentException {
        if (inputId == null)
            throw new IllegalArgumentException("Pet id is null");

        String cmd = "DELETE FROM Pet WHERE ID = ?";

        Optional<Pet> foundPet = findOne(inputId);
        foundPet.ifPresent(owner -> jdbcOperations.update(cmd, inputId));
        return foundPet;
    }

    @Override
    public Optional<Pet> update(Pet entity) throws IllegalArgumentException, ValidatorException {
        this.validator.validate(entity);

        String cmd = "UPDATE Pet SET Species = ?, Breed = ?, Name = ?, DateOfEnrolment = ?, PersonId = ?  WHERE ID = ?";

        try {
            Integer success = jdbcOperations.update(cmd, entity.getSpecies(), entity.getBreed(),
                    entity.getName(), entity.getDateOfEnrolment(), entity.getPersonId(), entity.getId());
            if (success.equals(1)) {
                return Optional.empty();
            }
            return Optional.of(entity);
        } catch (Exception e) {
            return Optional.of(entity);
        }
    }
}
