package ro.ubb.catalog.Repository.Database;

import ro.ubb.catalog.Domain.EmployeePet;
import ro.ubb.catalog.Domain.Validators.ValidatorException;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class EmployeePetDbRepository extends DbRepository<Long, EmployeePet>  {
    public EmployeePetDbRepository(String url, String user, String password) {
        super(url, user, password);

        //#TODO: make foreign key
        String createStmt = "CREATE TABLE IF NOT EXISTS EmployeePets(" +
                "ID INT PRIMARY KEY," +
                "EmployeeId INT," +
                "PetId INT," +
                "TypeOfAction VARCHAR(50)," +
                "Date VARCHAR(50))";
        try (var preparedStatement = super.connect(createStmt)) {
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Optional<EmployeePet> findOne(Long inputId) {
        String cmd = "SELECT * FROM EmployeePets WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setLong(1, inputId);
            var resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("ID");
                int employeeId = resultSet.getInt("EmployeeId");
                int petId = resultSet.getInt("PetId");
                String typeOfAction = resultSet.getString("TypeOfAction");
                String date = resultSet.getString("Date");

                var employeePet = new EmployeePet(employeeId, petId, typeOfAction, date);
                employeePet.setId(id);
                return Optional.ofNullable(employeePet);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<EmployeePet> findAll() {
        List<EmployeePet> surgeries = new ArrayList<>();
        String cmd = "SELECT * FROM EmployeePets";
        try (var preparedStatement = super.connect(cmd)) {
            var resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("ID");
                int employeeId = resultSet.getInt("EmployeeId");
                int petId = resultSet.getInt("PetId");
                String typeOfAction = resultSet.getString("TypeOfAction");
                String date = resultSet.getString("Date");

                var employeePet = new EmployeePet(employeeId, petId, typeOfAction, date);
                employeePet.setId(id);
                surgeries.add(employeePet);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return surgeries;
    }

    @Override
    public Optional<EmployeePet> save(EmployeePet entity) throws ValidatorException {
        String cmd = "INSERT INTO EmployeePets (ID, EmployeeId, PetId, TypeOfAction, Date) VALUES (?, ?, ?, ?, ?)";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setInt(1, entity.getEmployeeId());
            preparedStatement.setInt(2, entity.getPetId());
            preparedStatement.setString(3, entity.getTypeOfAction());
            preparedStatement.setString(4, entity.getDate());
            preparedStatement.setLong(5, entity.getId());

            preparedStatement.executeUpdate();
            return Optional.empty();
        } catch (SQLException sqlIntegrityConstraintViolationException) {
            return Optional.ofNullable(entity);
        }
    }

    @Override
    public Optional<EmployeePet> delete(Long aLong) {
        Optional<EmployeePet> v = findOne(aLong);
        String cmd = "DELETE FROM EmployeePet WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setLong(1, aLong);
            preparedStatement.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return v;
    }

    @Override
    public Optional<EmployeePet> update(EmployeePet entity) throws ValidatorException {
        String cmd = "UPDATE EmployeePets SET EmployeeId = ?, PetId = ?, TypeOfAction = ?, Date = ? WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setLong(1, entity.getId());
            preparedStatement.setInt(2, entity.getEmployeeId());
            preparedStatement.setInt(3, entity.getPetId());
            preparedStatement.setString(4, entity.getTypeOfAction());
            preparedStatement.setString(5, entity.getDate());
            preparedStatement.executeUpdate();
            return Optional.of(entity);
        } catch (SQLException sqlIntegrityConstraintViolationException) {
            System.out.println("Integrity constraint violation");
            return Optional.empty();
        }
    }
}
