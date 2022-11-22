package ro.ubb.catalog.Repository.Database;

import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Domain.EmployeeContract;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class EmployeeContractDbRepo extends DbRepository<Long, EmployeeContract> {
    public EmployeeContractDbRepo(String url, String user, String password) {
        super(url, user, password);

        String createStmt = "CREATE TABLE IF NOT EXISTS EMPLOYEECONTRACTS (ID INT PRIMARY KEY, Date VARCHAR(50), ClinicID INT, EmployeeID INT)";
        try (var preparedStatement = super.connect(createStmt)) {
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Optional<EmployeeContract> findOne(Long inputId) {
        String cmd = "SELECT * FROM EMPLOYEECONTRACTS WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setLong(1, inputId);
            var resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String date = resultSet.getString("date");
                int cid = resultSet.getInt("clinicid");
                int eid = resultSet.getInt("employeeid");
                var employeecontract = new EmployeeContract(LocalDate.parse(date), eid, cid);
                employeecontract.setId(id);
                return Optional.ofNullable(employeecontract);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<EmployeeContract> findAll() {
        List<EmployeeContract> ecs = new ArrayList<>();
        String cmd = "SELECT * FROM EMPLOYEECONTRACTS";
        try (var preparedStatement = super.connect(cmd)) {
            var resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String date = resultSet.getString("date");
                int cid = resultSet.getInt("clinicid");
                int eid = resultSet.getInt("employeeid");
                var employeecontract = new EmployeeContract(LocalDate.parse(date), eid, cid);
                employeecontract.setId(id);
                ecs.add(employeecontract);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return ecs;
    }

    @Override
    public Optional<EmployeeContract> save(EmployeeContract entity) throws ValidatorException {
        String cmd = "INSERT INTO EMPLOYEECONTRACTS (ID, Date, ClinicID, EmployeeID) VALUES (?, ?, ?, ?)";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setLong(1, entity.getId());
            preparedStatement.setString(2, entity.getDate().toString());
            preparedStatement.setInt(3, entity.getClinicID());
            preparedStatement.setInt(4, entity.getEmployeeID());

            preparedStatement.executeUpdate();
            return Optional.empty();
        } catch (SQLException sqlIntegrityConstraintViolationException) {
            return Optional.ofNullable(entity);
        }
    }

    @Override
    public Optional<EmployeeContract> delete(Long aLong) {
        Optional<EmployeeContract> ec = findOne(aLong);
        String cmd = "DELETE FROM EMPLOYEECONTRACTS WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setLong(1, aLong);
            preparedStatement.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return ec;
    }

    @Override
    public Optional<EmployeeContract> update(EmployeeContract entity) throws ValidatorException {
        String cmd = "UPDATE EMPLOYEECONTRACTS SET Date = ?, ClinicID = ?, EmployeeID = ? WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setString(1, entity.getDate().toString());
            preparedStatement.setInt(2, entity.getClinicID());
            preparedStatement.setInt(3, entity.getEmployeeID());
            preparedStatement.setLong(4, entity.getId());
            preparedStatement.executeUpdate();
            return Optional.of(entity);
        } catch (SQLException sqlIntegrityConstraintViolationException) {
            System.out.println("Integrity constraint violation");
            return Optional.empty();
        }
    }
}