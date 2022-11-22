package ro.ubb.catalog.Repository.Database;

import ro.ubb.catalog.Domain.Validators.Validator;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Domain.Pet;
import ro.ubb.catalog.Domain.Vet;
import ro.ubb.catalog.Repository.Database.DbRepository;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Optional;
import java.util.*;
import java.util.concurrent.atomic.AtomicReference;

public class PetDbRepo extends DbRepository<Long, Pet> {
    public PetDbRepo(String url, String user, String password) {
        super(url, user, password);

        String createStmt = "CREATE TABLE IF NOT EXISTS PETS( ID INT PRIMARY KEY, Species VARCHAR(50),Breed VARCHAR(50),PetName VARCHAR(50), PersonId INT)";
        try (var preparedStatement = super.connect(createStmt)) {
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Optional<Pet> findOne(Long inputId) {
        String cmd = "SELECT * FROM PETS WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setLong(1, inputId);
            var resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String species = resultSet.getString("species");
                String breed = resultSet.getString("breed");
                String petName = resultSet.getString("petName");
                int personId = resultSet.getInt("personId");


                var pet = new Pet(species, breed, petName, personId);
                pet.setId(id);
                return Optional.ofNullable(pet);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Pet> findAll() {
        List<Pet> pets = new ArrayList<>();
        String cmd = "SELECT * FROM pets";
        try (var preparedStatement = super.connect(cmd)) {
            var resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String species = resultSet.getString("species");
                String breed = resultSet.getString("breed");
                String petName = resultSet.getString("petName");
                int personId = resultSet.getInt("personId");


                var pet = new Pet(species, breed, petName, personId);
                pet.setId(id);
                pets.add(pet);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return pets;
    }

    @Override
    public Optional<Pet> save(Pet entity) throws ValidatorException {
        String cmd = "INSERT INTO PETS (ID, Species, Breed, PetName, PersonId) VALUES (?, ?, ?, ?, ?)";
        try (var preparedStatement = super.connect(cmd)){
            preparedStatement.setLong(1, entity.getId());
            preparedStatement.setString(2, entity.getSpecies());
            preparedStatement.setString(3, entity.getBreed());
            preparedStatement.setString(4, entity.getPetName());
            preparedStatement.setInt(5, entity.getPersonId());


            preparedStatement.executeUpdate();
            return Optional.empty();
        } catch (SQLException sqlIntegrityConstraintViolationException) {
            return Optional.ofNullable(entity);
        }
    }

    @Override
    public Optional<Pet> delete(Long aLong) {
        Optional<Pet> v = findOne(aLong);
        String cmd = "DELETE FROM PETS WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd))  {
            preparedStatement.setLong(1, aLong);
            preparedStatement.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return v;
    }

    @Override
    public Optional<Pet> update(Pet entity) throws ValidatorException {
        String cmd = "UPDATE PETS SET Species = ?, Breed = ?, PetName = ?, PersonId = ? WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setString(1, entity.getSpecies());
            preparedStatement.setString(2, entity.getBreed());
            preparedStatement.setString(3, entity.getPetName());
            preparedStatement.setInt(4, entity.getPersonId());
            preparedStatement.setLong(5, entity.getId());
            preparedStatement.executeUpdate();
            return Optional.of(entity);
        } catch (SQLException sqlIntegrityConstraintViolationException) {
            System.out.println("Integrity constraint violation");
            return Optional.empty();
        }

    }
}