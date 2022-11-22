package Server.Repository;

import Common.Model.Domain.Owner;
import Common.Model.Validators.IValidator;
import Common.Model.Validators.ValidatorException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcOperations;

import java.util.Optional;

public class OwnerRepository implements IRepository<Long, Owner> {
    private final IValidator<Owner> validator;
    @Autowired
    private JdbcOperations jdbcOperations;

    public OwnerRepository(IValidator<Owner> validator) {
        this.validator = validator;
    }

    @Override
    public Optional<Owner> findOne(Long inputId) throws IllegalArgumentException {
        if (inputId == null)
            throw new IllegalArgumentException("Owner id is null");

        String cmd = "SELECT * FROM Owner WHERE ID = " + inputId;

        return jdbcOperations.query(cmd, (rs, i) -> {
            String firstName = rs.getString("FirstName");
            String lastName = rs.getString("LastName");
            String email = rs.getString("Email");
            String phoneNumber = rs.getString("PhoneNumber");
            String dateOfBirth = rs.getString("DateOfBirth");

            return new Owner(inputId, firstName, lastName, email, phoneNumber, dateOfBirth);
        }).stream().findFirst();
    }

    @Override
    public Iterable<Owner> findAll() {
        String cmd = "SELECT * FROM Owner";

        return jdbcOperations.query(cmd, (rs, i) -> {
            Long id = rs.getLong("Id");
            String firstName = rs.getString("FirstName");
            String lastName = rs.getString("LastName");
            String email = rs.getString("Email");
            String phoneNumber = rs.getString("PhoneNumber");
            String dateOfBirth = rs.getString("DateOfBirth");

            return new Owner(id, firstName, lastName, email, phoneNumber, dateOfBirth);
        });
    }

    @Override
    public Optional<Owner> save(Owner entity) throws IllegalArgumentException, ValidatorException {
        this.validator.validate(entity);

        String cmd = "INSERT INTO Owner (FirstName, LastName, Email, PhoneNumber, DateOfBirth) VALUES (?, ?, ?, ?, ?)";

        try {
            Integer success = jdbcOperations.update(cmd, entity.getFirstName(), entity.getLastName(),
                    entity.getEmail(), entity.getPhoneNumber(), entity.getDateOfBirth());
            if (success.equals(1)) {
                return Optional.empty();
            }
            return Optional.of(entity);
        } catch (Exception e) {
            return Optional.of(entity);
        }
    }

    @Override
    public Optional<Owner> delete(Long inputId) throws IllegalArgumentException {
        if (inputId == null)
            throw new IllegalArgumentException("Owner id is null");

        String cmd = "DELETE FROM Owner WHERE ID = ?";

        Optional<Owner> foundOwner = findOne(inputId);
        foundOwner.ifPresent(owner -> jdbcOperations.update(cmd, inputId));
        return foundOwner;
    }

    @Override
    public Optional<Owner> update(Owner entity) throws IllegalArgumentException, ValidatorException {
        this.validator.validate(entity);

        String cmd = "UPDATE Owner SET FirstName = ?, LastName = ?, Email = ?, PhoneNumber = ?, DateOfBirth = ?  WHERE ID = ?";

        try {
            Integer success = jdbcOperations.update(cmd, entity.getFirstName(), entity.getLastName(), entity.getEmail(),
                    entity.getPhoneNumber(), entity.getDateOfBirth(), entity.getId());
            if (success.equals(1)) {
                return Optional.empty();
            }
            return Optional.of(entity);
        } catch (Exception e) {
            return Optional.of(entity);
        }
    }
}
