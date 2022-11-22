package ro.ubb.catalog.Repository.Database;

import ro.ubb.catalog.Domain.Owner;
import ro.ubb.catalog.Domain.Validators.Validator;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Repository.Database.DbRepository;


import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Optional;
import java.util.*;
import java.util.concurrent.atomic.AtomicReference;

public class OwnerDbRepo extends DbRepository<Long, Owner> {


    public OwnerDbRepo(String url, String user, String password) {
        super(url,user, password);


        String createStmt = "CREATE TABLE IF NOT EXISTS OWNER(ID INT PRIMARY KEY, FirstName VARCHAR(50), LastName VARCHAR(50))";
        try (Connection connect = DriverManager.getConnection(url, user, password)) {
            var preparedStatement = connect.prepareStatement(createStmt);
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Optional<Owner> findOne(Long inputId){
        String cmd = "SELECT * FROM owner WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd)) {

            preparedStatement.setLong(1, inputId);
            var resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String firstName = resultSet.getString("firstname");
                String lastName = resultSet.getString("lastname");

                var owner = new Owner(firstName, lastName);
                owner.setId(id);
                return Optional.ofNullable(owner);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Owner> findAll() {
        List<Owner> owners = new ArrayList<>();
        String cmd = "SELECT * FROM owner";
        try (var preparedStatement = super.connect(cmd)) {
            var resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String firstName = resultSet.getString("firstname");
                String lastName = resultSet.getString("lastname");

                var owner = new Owner(firstName, lastName);
                owner.setId(id);
                owners.add(owner);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return owners;
    }

    @Override
    public Optional<Owner> save(Owner entity) throws ValidatorException,IllegalArgumentException {
        String cmd = "INSERT INTO owner (ID, FirstName, LastName) VALUES (?, ?, ?)";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setLong(1, entity.getId());
            preparedStatement.setString(2, entity.getFirstName());
            preparedStatement.setString(3, entity.getLastName());

            preparedStatement.executeUpdate();
            return Optional.empty();
        } catch (SQLException sqlIntegrityConstraintViolationException) {
            return Optional.ofNullable(entity);
        }
    }

    @Override
    public Optional<Owner> delete(Long aLong) {
        Optional<Owner> v = findOne(aLong);
        String cmd = "DELETE FROM OWNER WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setLong(1, aLong);
            preparedStatement.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return v;
    }

    @Override
    public Optional<Owner> update(Owner entity) throws ValidatorException ,IllegalArgumentException{
        String cmd = "UPDATE Owner SET FirstName = ?, LastName = ? WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setString(1, entity.getFirstName());
            preparedStatement.setString(2, entity.getLastName());
            preparedStatement.setLong(3, entity.getId());
            preparedStatement.executeUpdate();
            return Optional.of(entity);
        } catch (SQLException sqlIntegrityConstraintViolationException) {
            System.out.println("Integrity constraint violation");
            return Optional.empty();
        }
    }
}
