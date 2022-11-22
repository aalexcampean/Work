package ro.ubb.catalog.Repository.Database;

import ro.ubb.catalog.Domain.Surgery;
import ro.ubb.catalog.Domain.Validators.ValidatorException;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class SurgeryDbRepository extends DbRepository<Long, Surgery>  {
    public SurgeryDbRepository(String url, String user, String password) {
        super(url, user, password);

        //#TODO: make foreign key
        String createStmt = "CREATE TABLE IF NOT EXISTS Surgeries(" +
                "ID INT PRIMARY KEY," +
                "PetId INT," +
                "VetId INT," +
                "SurgeryDate VARCHAR(50)," +
                "SurgeryType VARCHAR(50))";
        try (var preparedStatement = super.connect(createStmt)) {
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Optional<Surgery> findOne(Long inputId) {
        String cmd = "SELECT * FROM Surgeries WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setLong(1, inputId);
            var resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("ID");
                int petId = resultSet.getInt("PetId");
                int vetId = resultSet.getInt("VetId");
                String surgeryDate = resultSet.getString("SurgeryDate");
                String surgeryType = resultSet.getString("SurgeryType");

                var surgery = new Surgery(petId, vetId, surgeryDate, surgeryType);
                surgery.setId(id);
                return Optional.ofNullable(surgery);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Surgery> findAll() {
        List<Surgery> surgeries = new ArrayList<>();
        String cmd = "SELECT * FROM Surgeries";
        try (var preparedStatement = super.connect(cmd)) {
            var resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("ID");
                int petId = resultSet.getInt("PetId");
                int vetId = resultSet.getInt("VetId");
                String surgeryDate = resultSet.getString("SurgeryDate");
                String surgeryType = resultSet.getString("SurgeryType");

                var surgery = new Surgery(petId, vetId, surgeryDate, surgeryType);
                surgery.setId(id);
                surgeries.add(surgery);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return surgeries;
    }

    @Override
    public Optional<Surgery> save(Surgery entity) throws ValidatorException {
        String cmd = "INSERT INTO Surgeries (ID, PetId, VetId, SurgeryDate, SurgeryType) VALUES (?, ?, ?, ?, ?)";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setLong(1, entity.getId());
            preparedStatement.setInt(2, entity.getPetId());
            preparedStatement.setInt(3, entity.getVetId());
            preparedStatement.setString(4, entity.getSurgeryDate());
            preparedStatement.setString(5, entity.getSurgeryType());

            preparedStatement.executeUpdate();
            return Optional.empty();
        } catch (SQLException sqlIntegrityConstraintViolationException) {
            return Optional.ofNullable(entity);
        }
    }

    @Override
    public Optional<Surgery> delete(Long aLong) {
        Optional<Surgery> v = findOne(aLong);
        String cmd = "DELETE FROM Surgeries WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setLong(1, aLong);
            preparedStatement.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return v;
    }

    @Override
    public Optional<Surgery> update(Surgery entity) throws ValidatorException {
        String cmd = "UPDATE Surgeries SET PetId = ?, VetId = ?, SurgeryDate = ?, SurgeryType = ? WHERE ID = ?";
        try (var preparedStatement = super.connect(cmd)) {
            preparedStatement.setInt(1, entity.getPetId());
            preparedStatement.setInt(2, entity.getVetId());
            preparedStatement.setString(3, entity.getSurgeryDate());
            preparedStatement.setString(4, entity.getSurgeryType());
            preparedStatement.setLong(5, entity.getId());
            preparedStatement.executeUpdate();
            return Optional.of(entity);
        } catch (SQLException sqlIntegrityConstraintViolationException) {
            System.out.println("Integrity constraint violation");
            return Optional.empty();
        }
    }
}
