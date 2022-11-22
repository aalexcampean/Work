package ro.ubb.catalog.Repository.Database;

import ro.ubb.catalog.Domain.Clinic;
import ro.ubb.catalog.Domain.VetContract;

import java.sql.SQLException;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class VetContractDbRepo extends DbRepository<Long, VetContract> {
    public VetContractDbRepo(String url, String user, String password) {
        super(url, user, password);
        String createStmt =
                "CREATE TABLE IF NOT EXISTS VetContract" +
                        "( ID INT PRIMARY KEY," +
                        "VetID INT," +
                        "ClinicID INT," +
                        "ContractDate VARCHAR(10)" +
                        ")";

        try (var preparedStatement = super.connect(createStmt)) {
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Optional<VetContract> findOne(Long paramId) {
        String sqlStmt = "SELECT * FROM VetContract WHERE ID = ?";
        try (var preparedStatement = super.connect(sqlStmt)) {
            preparedStatement.setLong(1, paramId);

            var resultSet = preparedStatement.executeQuery();

            while (!resultSet.next()) {
                Long id = resultSet.getLong("ID");
                int vetId = resultSet.getInt("VetId");
                int clinicId = resultSet.getInt("ClinicId");
                LocalDate contractDate = LocalDate.parse(resultSet.getString("ContractDate"));

                VetContract vetContract = new VetContract(vetId, clinicId, contractDate);
                vetContract.setId(id);
                return Optional.of(vetContract);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<VetContract> findAll() {
        List<VetContract> vetContractList = new ArrayList<>();

        String sqlStmt = "SELECT * FROM VetContract";

        try (var preparedStatement = super.connect(sqlStmt)) {
            var resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                Long id = resultSet.getLong("ID");
                int vetId = resultSet.getInt("VetId");
                int clinicId = resultSet.getInt("ClinicId");
                LocalDate contractDate = LocalDate.parse(resultSet.getString("ContractDate"));

                VetContract vetContract = new VetContract(vetId, clinicId, contractDate);
                vetContract.setId(id);
                vetContractList.add(vetContract);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return vetContractList;
    }

    @Override
    public Optional<VetContract> save(VetContract entity) {
        String sqlStmt = "INSERT INTO VetContract (VetId , ClinicId, ContractDate) VALUES (?, ?, ?)";
        try (var preparedStatement = super.connect(sqlStmt)) {
            preparedStatement.setInt(1, entity.getVetID());
            preparedStatement.setInt(2, entity.getClinicID());
            preparedStatement.setString(3, entity.getContractDate().toString());

            preparedStatement.executeUpdate();
            return Optional.empty();
        } catch (SQLException e) {
            e.printStackTrace();
            return Optional.of(entity);
        }
    }

    @Override
    public Optional<VetContract> delete(Long paramId) {
        Optional<VetContract> vetContract = findOne(paramId);
        String sqlStmt = "DELETE FROM VetContract WHERE ID = ?";
        try (var preparedStatement = super.connect(sqlStmt)) {
            preparedStatement.setLong(1, paramId);
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return vetContract;
    }

    @Override
    public Optional<VetContract> update(VetContract entity) {
        String sqlStmt = "UPDATE VetContract" +
                        "SET VetId=?, ClinicId=?, ContractDate=?" +
                        "WHERE ID = ?";

        try (var preparedStatement = super.connect(sqlStmt)) {
            preparedStatement.setInt(1, entity.getVetID());
            preparedStatement.setInt(2, entity.getClinicID());
            preparedStatement.setString(3, entity.getContractDate().toString());
            preparedStatement.setLong(4, entity.getId());

            preparedStatement.executeUpdate();
            return Optional.empty();
        } catch (SQLException e) {
            e.printStackTrace();
            return Optional.of(entity);
        }
    }
}
