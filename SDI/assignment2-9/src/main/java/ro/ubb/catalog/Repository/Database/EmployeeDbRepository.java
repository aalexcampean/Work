package ro.ubb.catalog.Repository.Database;

import ro.ubb.catalog.Domain.Employee;
import ro.ubb.catalog.Domain.Validators.ValidatorException;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class EmployeeDbRepository extends DbRepository<Long, Employee> {

    public EmployeeDbRepository(String url, String user, String password) {
        super(url, user, password);

        String createStmt = "CREATE TABLE IF NOT EXISTS EMPLOYEES(" +
                "ID INT PRIMARY KEY," +
                "FirstName VARCHAR(50)," +
                "LastName VARCHAR(50)," +
                "Salary INT," +
                "Rating INT," +
                "Date VARCHAR(50))";
        try (var preparedStatement = super.connect(createStmt)) {
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Optional<Employee> findOne(Long inputId) {
        String cmd = "SELECT * FROM EMPLOYEES WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setLong(1, inputId);
            var resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String firstName = resultSet.getString("FirstName");
                String lastName = resultSet.getString("LastName");
                int salary = resultSet.getInt("Salary");
                int rating = resultSet.getInt("Rating");
                String date = resultSet.getString("Date");

                var employee = new Employee(firstName, lastName, salary, rating, date);
                employee.setId(id);
                return Optional.ofNullable(employee);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Employee> findAll() {
        List<Employee> employees = new ArrayList<>();
        String cmd = "SELECT * FROM EMPLOYEES";
        try (var preparedStatement = super.connect(cmd)) {
            var resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("ID");
                String firstName = resultSet.getString("FirstName");
                String lastName = resultSet.getString("LastName");
                int salary = resultSet.getInt("Salary");
                int rating = resultSet.getInt("Rating");
                String date = resultSet.getString("Date");

                var employee = new Employee(firstName, lastName, salary, rating, date);
                employee.setId(id);
                employees.add(employee);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return employees;
    }

    @Override
    public Optional<Employee> save(Employee entity) throws ValidatorException {
        String cmd = "INSERT INTO EMPLOYEES (ID, FirstName, LastName, Salary, Rating, Date) VALUES (?, ?, ?, ?, ?, ?)";
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
    public Optional<Employee> delete(Long aLong) {
        Optional<Employee> employee = findOne(aLong);
        String cmd = "DELETE FROM EMPLOYEES WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setLong(1, aLong);
            preparedStatement.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return employee;
    }

    @Override
    public Optional<Employee> update(Employee entity) throws ValidatorException {
        String cmd = "UPDATE EMPLOYEES SET FirstName = ?, LastName = ?, Salary = ?, Rating = ?, Date = ? WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setString(1, entity.getFirstName());
            preparedStatement.setString(2, entity.getLastName());
            preparedStatement.setInt(3, entity.getSalary());
            preparedStatement.setInt(4, entity.getRating());
            preparedStatement.setString(5, entity.getDate());
            preparedStatement.setLong(6, entity.getId());
            preparedStatement.executeUpdate();
            return Optional.of(entity);
        } catch (SQLException sqlIntegrityConstraintViolationException) {
            System.out.println("Integrity constraint violation");
            return Optional.empty();
        }
    }
}
