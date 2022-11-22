package ro.ubb.catalog.Repository.Database;

import ro.ubb.catalog.Domain.Clinic;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class ClinicDbRepo extends DbRepository<Long, Clinic> {

    public ClinicDbRepo(String url, String user, String password) {
        super(url, user, password);
        // The sql command responsible for creating the associated table if it doesn't already exist
        String createStmt = "CREATE TABLE IF NOT EXISTS Clinic " +
                "(id INT GENERATED ALWAYS AS IDENTITY, " +
                "name VARCHAR(50) NOT NULL, " +
                "location VARCHAR(50) NOT NULL, " +
                "yearFounded INT NOT NULL, " +
                "CONSTRAINT PK_Clinic PRIMARY KEY (id))";
        // Executing the provided swl command
        try (var preparedStatement = super.connect(createStmt)) {
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Optional<Clinic> findOne(Long inputId) {
        String cmd = "SELECT * FROM Clinic WHERE id = ?";
        try (var preparedStatement = super.connect(cmd)) {
            // Injecting the desired id in the sql command
            preparedStatement.setLong(1, inputId);
            // Executing the sql command
            var resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String name = resultSet.getString("name");
                String location = resultSet.getString("location");
                int yearFounded = resultSet.getInt("yearFounded");

                Clinic clinic = new Clinic(name, location, yearFounded);
                clinic.setId(id);
                return Optional.of(clinic);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Clinic> findAll() {
        List<Clinic> clinics = new ArrayList<>();
        String cmd = "SELECT * FROM Clinic";
        try (var preparedStatement = super.connect(cmd)) {
            // Executing the sql command
            var resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String name = resultSet.getString("name");
                String location = resultSet.getString("location");
                int yearFounded = resultSet.getInt("yearFounded");

                Clinic clinic = new Clinic(name, location, yearFounded);
                clinic.setId(id);
                clinics.add(clinic);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return clinics;
    }

    @Override
    public Optional<Clinic> save(Clinic entity) {
        String cmd = "INSERT INTO Clinic (name, location, yearFounded) VALUES (?, ?, ?)";
        try (var preparedStatement = super.connect(cmd)) {
            // Injecting the desired id in the sql command
            preparedStatement.setString(1, entity.getName());
            preparedStatement.setString(2, entity.getLocation());
            preparedStatement.setInt(3, entity.getYearFounded());
            // Executing the sql command
            preparedStatement.executeUpdate();
            return Optional.empty();
        } catch (SQLException e) {
            e.printStackTrace();
            return Optional.of(entity);
        }
    }

    @Override
    public Optional<Clinic> delete(Long inputId) {
        Optional<Clinic> clinic = findOne(inputId);
        String cmd = "DELETE FROM Clinic WHERE id = ?";
        try (var preparedStatement = super.connect(cmd)) {
            // Injecting the desired id in the sql command
            preparedStatement.setLong(1, inputId);
            // Executing the sql command
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return clinic;
    }

    @Override
    public Optional<Clinic> update(Clinic entity) {
        String cmd = "UPDATE Clinic SET name = ?, location = ?, yearFounded = ? WHERE id = ?";
        try (var preparedStatement = super.connect(cmd)) {
            // Injecting the desired id in the sql command
            preparedStatement.setString(1, entity.getName());
            preparedStatement.setString(2, entity.getLocation());
            preparedStatement.setInt(3, entity.getYearFounded());
            preparedStatement.setLong(4, entity.getId());
            // Executing the sql command
            preparedStatement.executeUpdate();
            return Optional.empty();
        } catch (SQLException e) {
            e.printStackTrace();
            return Optional.of(entity);
        }
    }
}
