package Server.Repository;

import Common.Model.Domain.Appointment;
import Common.Model.Validators.IValidator;
import Common.Model.Validators.ValidatorException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcOperations;

import java.util.Optional;

public class AppointmentRepository implements IRepository<Long, Appointment> {
    private final IValidator<Appointment> validator;
    @Autowired
    private JdbcOperations jdbcOperations;

    public AppointmentRepository(IValidator<Appointment> validator) {
        this.validator = validator;
    }

    @Override
    public Optional<Appointment> findOne(Long inputId) throws IllegalArgumentException {
        if (inputId == null)
            throw new IllegalArgumentException("Appointment id is null");

        String cmd = "SELECT * FROM Appointment WHERE ID = " + inputId;

        return jdbcOperations.query(cmd, (rs, i) -> {
            Long species = rs.getLong("PetId");
            Long breed = rs.getLong("VetId");
            String type = rs.getString("Type");
            String date = rs.getString("Date");

            return new Appointment(inputId, species, breed, type, date);
        }).stream().findFirst();
    }

    @Override
    public Iterable<Appointment> findAll() {
        String cmd = "SELECT * FROM Appointment";

        return jdbcOperations.query(cmd, (rs, i) -> {
            Long id = rs.getLong("Id");
            Long species = rs.getLong("PetId");
            Long breed = rs.getLong("VetId");
            String type = rs.getString("Type");
            String date = rs.getString("Date");

            return new Appointment(id, species, breed, type, date);
        });
    }

    @Override
    public Optional<Appointment> save(Appointment entity) throws IllegalArgumentException, ValidatorException {
        this.validator.validate(entity);

        String cmd = "INSERT INTO Appointment (PetId, VetId, Type, Date) VALUES (?, ?, ?, ?)";

        try {
            Integer success = jdbcOperations.update(cmd, entity.getPetId(), entity.getVetId(),
                    entity.getType(), entity.getDate());
            if (success.equals(1)) {
                return Optional.empty();
            }
            return Optional.of(entity);
        } catch (Exception e) {
            return Optional.of(entity);
        }
    }

    @Override
    public Optional<Appointment> delete(Long inputId) throws IllegalArgumentException {
        if (inputId == null)
            throw new IllegalArgumentException("Appointment id is null");

        String cmd = "DELETE FROM Appointment WHERE ID = ?";

        Optional<Appointment> foundPet = findOne(inputId);
        foundPet.ifPresent(owner -> jdbcOperations.update(cmd, inputId));
        return foundPet;
    }

    @Override
    public Optional<Appointment> update(Appointment entity) throws IllegalArgumentException, ValidatorException {
        this.validator.validate(entity);

        String cmd = "UPDATE Appointment SET PetId = ?, VetId = ?, Type = ?, Date = ? WHERE ID = ?";

        try {
            Integer success = jdbcOperations.update(cmd, entity.getPetId(), entity.getVetId(),
                    entity.getType(), entity.getDate(), entity.getId());
            if (success.equals(1)) {
                return Optional.empty();
            }
            return Optional.of(entity);
        } catch (Exception e) {
            return Optional.of(entity);
        }
    }
}
