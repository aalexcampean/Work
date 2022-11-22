package Server.Repository;

import Common.Model.Domain.Vet;
import Common.Model.Validators.IValidator;
import Common.Model.Validators.ValidatorException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcOperations;

import java.util.Optional;

public class VetRepository implements IRepository<Long, Vet> {
    private final IValidator<Vet> validator;
    @Autowired
    private JdbcOperations jdbcOperations;

    public VetRepository(IValidator<Vet> validator) {
        this.validator = validator;
    }

    @Override
    public Optional<Vet> findOne(Long inputId) throws IllegalArgumentException {
        if (inputId == null)
            throw new IllegalArgumentException("Vet id is null");

        String cmd = "SELECT * FROM Vet WHERE ID = " + inputId;

        return jdbcOperations.query(cmd, (rs, i) -> {
            String firstName = rs.getString("FirstName");
            String lastName = rs.getString("LastName");
            String email = rs.getString("Email");
            String phoneNumber = rs.getString("PhoneNumber");
            String dateOfBirth = rs.getString("DateOfBirth");
            Integer salary = rs.getInt("Salary");
            Integer rating = rs.getInt("Rating");

            return new Vet(inputId, firstName, lastName, email, phoneNumber, dateOfBirth, salary, rating);
        }).stream().findFirst();
    }

    @Override
    public Iterable<Vet> findAll() {
        String cmd = "SELECT * FROM Vet";

        return jdbcOperations.query(cmd, (rs, i) -> {
            Long id = rs.getLong("Id");
            String firstName = rs.getString("FirstName");
            String lastName = rs.getString("LastName");
            String email = rs.getString("Email");
            String phoneNumber = rs.getString("PhoneNumber");
            String dateOfBirth = rs.getString("DateOfBirth");
            Integer salary = rs.getInt("Salary");
            Integer rating = rs.getInt("Rating");

            return new Vet(id, firstName, lastName, email, phoneNumber, dateOfBirth, salary, rating);
        });
    }

    @Override
    public Optional<Vet> save(Vet entity) throws IllegalArgumentException, ValidatorException {
        this.validator.validate(entity);

        String cmd = "INSERT INTO Vet (FirstName, LastName, Email, PhoneNumber, DateOfBirth, Salary, Rating) VALUES (?, ?, ?, ?, ?, ?, ?)";

        try {
            Integer success = jdbcOperations.update(cmd, entity.getFirstName(), entity.getLastName(),
                    entity.getEmail(), entity.getPhoneNumber(), entity.getDateOfBirth(), entity.getSalary(), entity.getRating());
            if (success.equals(1)) {
                return Optional.empty();
            }
            return Optional.of(entity);
        } catch (Exception e) {
            return Optional.of(entity);
        }
    }

    @Override
    public Optional<Vet> delete(Long inputId) throws IllegalArgumentException {
        if (inputId == null)
            throw new IllegalArgumentException("Vet id is null");

        String cmd = "DELETE FROM Vet WHERE ID = ?";

        Optional<Vet> foundVet = findOne(inputId);
        foundVet.ifPresent(owner -> jdbcOperations.update(cmd, inputId));
        return foundVet;
    }

    @Override
    public Optional<Vet> update(Vet entity) throws IllegalArgumentException, ValidatorException {
        this.validator.validate(entity);

        String cmd = "UPDATE Vet SET FirstName = ?, LastName = ?, Email = ?, PhoneNumber = ?, DateOfBirth = ?, Salary = ?, Rating = ?  WHERE ID = ?";

        try {
            Integer success = jdbcOperations.update(cmd, entity.getFirstName(), entity.getLastName(), entity.getEmail(),
                    entity.getPhoneNumber(), entity.getDateOfBirth(), entity.getSalary(), entity.getRating(), entity.getId());
            if (success.equals(1)) {
                return Optional.empty();
            }
            return Optional.of(entity);
        } catch (Exception e) {
            return Optional.of(entity);
        }
    }
}
