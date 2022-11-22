package ro.ubb.catalog.Service;

import ro.ubb.catalog.Domain.Surgery;
import ro.ubb.catalog.Domain.Validators.SurgeryValidator;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Repository.Repository;

import java.util.HashSet;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class SurgeryService {
    private Repository<Long, Surgery> repository;
    private SurgeryValidator surgeryValidator;

    public SurgeryService(Repository<Long, Surgery> repository, SurgeryValidator surgeryValidator) {
        this.repository = repository;
        this.surgeryValidator = surgeryValidator;
    }

    /**
     * Add a surgery
     * @param surgery - the surgery to be added
     * @throws ValidatorException - throw exception in case the surgery is not valid
     */
    public void addSurgery(Surgery surgery) throws ValidatorException {
        this.surgeryValidator.validate(surgery);
        this.repository.save(surgery);
    }

    /**
     * Delete a surgery
     * @param surgeryId Long - the id of the surgery to be deleted
     */
    public void deleteSurgery(Long surgeryId) {
        repository.delete(surgeryId);
    }

    /**
     * Update a surgery
     * @param surgery - the surgery with the new attributes
     */
    public void updateSurgery(Surgery surgery) {
        repository.update(surgery);
    }

    /**
     * Returns all the surgeries
     * @return all surgeries
     */
    public Set<Surgery> getAllSurgeries() {
        Iterable<Surgery> surgeries = this.repository.findAll();
        return StreamSupport.stream(surgeries.spliterator(), false).collect(Collectors.toSet());
    }

    /**
     * Returns all the surgeries that have the given surgery type.
     * @param s String - the surgery type for filtering
     * @return filtered surgeries
     */
    public Set<Surgery> filterSurgeriesByType(String s) {
        Iterable<Surgery> surgeries = repository.findAll();
        Set<Surgery> filteredSurgeries= new HashSet<>();
        surgeries.forEach(filteredSurgeries::add);
        filteredSurgeries.removeIf(surgery -> !surgery.getSurgeryType().contains(s));

        return filteredSurgeries;
    }
}
