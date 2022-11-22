package ro.ubb.catalog.Service;

import ro.ubb.catalog.Domain.Clinic;
import ro.ubb.catalog.Domain.Validators.Validator;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Repository.Repository;

import java.util.Optional;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class ClinicService {
    private Repository<Long, Clinic> repository;
    private Validator<Clinic> validator;

    public ClinicService(Repository<Long, Clinic> repository, Validator<Clinic> validator) {
        this.repository = repository;
        this.validator = validator;
    }

    /**
     * Add a clinic if it doesn't already exist
     *
     * @param clinic
     * @throws ValidatorException
     */
    public void addClinic(Clinic clinic) throws ValidatorException, IllegalArgumentException {
        this.validator.validate(clinic);
        this.repository.save(clinic);
    }

    /**
     * Deletes a clinic if it exists
     *
     * @param id
     * @return the deleted Clinic if it exists
     */
    public Optional<Clinic> deleteClinic(Long id) throws IllegalArgumentException {
        if (id == null) {
            throw new IllegalArgumentException("Null clinic ID");
        }
        return this.repository.delete(id);
    }

    /**
     * Updates a clinic if it exists
     *
     * @param clinic
     * @return the updated Clinic if it exists
     */
    public Optional<Clinic> updateClinic(Clinic clinic) throws ValidatorException, IllegalArgumentException {
        this.validator.validate(clinic);
        return this.repository.update(clinic);
    }

    /**
     * Return all clinics
     *
     * @return all clinics
     */
    public Set<Clinic> getAllClinics() {
        Iterable<Clinic> clinics = repository.findAll();
        return StreamSupport.stream(clinics.spliterator(), false)
                .collect(Collectors.toSet());
    }

    /**
     * Filter all clinics founded earlier than a given year
     *
     * @param inputYear Integer the input year
     * @return filtered clinics
     */
    public Set<Clinic> filterClinicsFoundedBeforeDate(Integer inputYear) {
        Iterable<Clinic> clinics = repository.findAll();

        return StreamSupport.stream(clinics.spliterator(), false)
                .filter(clinic -> clinic.getYearFounded() < inputYear)
                .collect(Collectors.toSet());
    }
}
