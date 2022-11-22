package ro.ubb.catalog.Repository.Database;

import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Domain.Vet;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class VetDbRepo extends DbRepository<Long, Vet> {
    public VetDbRepo(String url, String user, String password) {
        super(url, user, password);

        String createStmt = "CREATE TABLE IF NOT EXISTS VETS( ID INT PRIMARY KEY, FirstName VARCHAR(50), LastName VARCHAR(50), Salary INT, Rating INT, Date VARCHAR(50))";
        try (var preparedStatement = super.connect(createStmt)) {
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Optional<Vet> findOne(Long inputId) {
        String cmd = "SELECT * FROM vets WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setLong(1, inputId);
            var resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String firstName = resultSet.getString("firstname");
                String lastName = resultSet.getString("lastname");
                int salary = resultSet.getInt("salary");
                int rating = resultSet.getInt("rating");
                String date = resultSet.getString("date");

                var vet = new Vet(firstName, lastName, salary, rating, date);
                vet.setId(id);
                return Optional.ofNullable(vet);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Vet> findAll() {
        List<Vet> vets = new ArrayList<>();
        String cmd = "SELECT * FROM vets";
        try (var preparedStatement = super.connect(cmd)) {
            var resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String firstName = resultSet.getString("firstname");
                String lastName = resultSet.getString("lastname");
                int salary = resultSet.getInt("salary");
                int rating = resultSet.getInt("rating");
                String date = resultSet.getString("date");

                var vet = new Vet(firstName, lastName, salary, rating, date);
                vet.setId(id);
                vets.add(vet);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return vets;
    }

    @Override
    public Optional<Vet> save(Vet entity) {
        String cmd = "INSERT INTO VETS (ID, FirstName, LastName, Salary, Rating, Date) VALUES (?, ?, ?, ?, ?, ?)";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setLong(1, entity.getId());
            preparedStatement.setString(2, entity.getFirstName());
            preparedStatement.setString(3, entity.getLastName());
            preparedStatement.setInt(4, entity.getSalary());
            preparedStatement.setInt(5, entity.getRating());
            preparedStatement.setString(6, entity.getDate());

            preparedStatement.executeUpdate();
            return Optional.empty();
        } catch (SQLException sqlIntegrityConstraintViolationException) {
            return Optional.ofNullable(entity);
        }
    }

    @Override
    public Optional<Vet> delete(Long aLong) {
        Optional<Vet> v = findOne(aLong);
        String cmd = "DELETE FROM VETS WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setLong(1, aLong);
            preparedStatement.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return v;
    }

    @Override
    public Optional<Vet> update(Vet entity) {
        String cmd = "UPDATE VETS SET FirstName = ?, LastName = ?, Salary = ?, Rating = ?, Date = ? WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setString(1, entity.getFirstName());
            preparedStatement.setString(2, entity.getLastName());
            preparedStatement.setInt(3, entity.getSalary());
            preparedStatement.setInt(4, entity.getRating());
            preparedStatement.setString(5, entity.getDate());
            preparedStatement.setLong(6, entity.getId());
            preparedStatement.executeUpdate();
            return Optional.empty();
        } catch (SQLException sqlIntegrityConstraintViolationException) {
            System.out.println("Integrity constraint violation");
            return Optional.of(entity);
        }
    }
}