package Common.Model.Validators;

import Common.Model.Domain.Appointment;

import java.util.Objects;

public class AppointmentValidator implements IValidator<Appointment> {
    @Override
    public void validate(Appointment appointment) throws ValidatorException {
        if (appointment == null)
            throw new IllegalArgumentException("Appointment is null");

        if (appointment.getId() < 0)
            throw new ValidatorException("Invalid appointment id");

        if (appointment.getPetId() < 0)
            throw new ValidatorException("Invalid appointment pet id");

        if (appointment.getVetId() < 0)
            throw new ValidatorException("Invalid appointment vet id");

        if (Objects.equals(appointment.getType(), ""))
            throw new ValidatorException("Invalid appointment type");

        if (Objects.equals(appointment.getDate(), ""))
            throw new ValidatorException("Invalid appointment date");
    }
}
