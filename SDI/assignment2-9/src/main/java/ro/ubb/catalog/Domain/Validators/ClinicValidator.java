package ro.ubb.catalog.Domain.Validators;
import ro.ubb.catalog.Domain.Clinic;

public class ClinicValidator implements Validator<Clinic> {
    @Override
    public void validate(Clinic entity) throws ValidatorException, IllegalArgumentException {
        if (entity == null)
            throw new IllegalArgumentException("Null clinic");
        if(entity.getId() < 0)
            throw new ValidatorException("Invalid ClinicID");
        if (entity.getName().isEmpty())
            throw new ValidatorException("Invalid ClinicName");
        if (entity.getLocation().isEmpty())
            throw new ValidatorException("Invalid ClinicLocation");
        if (entity.getYearFounded() > 2021)
            throw new ValidatorException("Invalid ClinicYearFounded");
    }
}
