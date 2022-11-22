package web.controller;

import core.dto.AppointmentDTO;
import core.dto.PetDTO;
import core.dto.VetDTO;
import core.dto.collections.AppointmentsDTO;
import core.dto.collections.PetsDTO;
import core.dto.collections.VetsDTO;
import core.entity.Vet;
import core.service.interfaces.IVetService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.stream.Collectors;

@RestController
public class VetController {
    // Logger
    public static final Logger log = LoggerFactory.getLogger(VetController.class);
    // Dependencies
    @Autowired
    private IVetService vetService;

    @RequestMapping(value = "/vets")
    VetsDTO getVets() {
        log.trace("getVets --- method started");
        VetsDTO result = new VetsDTO(vetService.getVets()
                .stream()
                .map(vet -> new VetDTO().encode(vet))
                .collect(Collectors.toSet()));
        log.trace("getVets --- method finished: result={}", result);
        return result;
    }

    @RequestMapping(value = "/vets/pageNumber={pageNumber}&pageSize={pageSize}")
    VetsDTO getPaginatedVets(@PathVariable int pageNumber, @PathVariable int pageSize) {
        log.trace("getPaginatedVets --- method started");
        List<Vet> vets = vetService.getVets();
        Integer total = vets.size();
        if (pageSize != -1) {
            vets = vets.stream().skip((long) pageNumber * pageSize).limit(pageSize).collect(Collectors.toList());
        }
        VetsDTO result = new VetsDTO(vets.stream().map(vet -> new VetDTO().encode(vet)).collect(Collectors.toSet()), total);
        log.trace("getPaginatedVets --- method finished: result={}", result);
        return result;
    }

    @RequestMapping(value = "/vets/appointments/{id}")
    AppointmentsDTO getVetAppointments(@PathVariable Long id) {
        log.trace("getVetAppointments --- method started");
        AppointmentsDTO result = new AppointmentsDTO(vetService.getVetAppointments(id).stream()
                .map(appointment -> new AppointmentDTO().encode(appointment))
                .collect(Collectors.toSet()));
        log.trace("getVetAppointments --- method finished: result={}", result);
        return result;
    }

    @RequestMapping(value = "/vets/patients/{id}")
    PetsDTO getVetPatients(@PathVariable Long id) {
        log.trace("getVetPatients --- method started");
        PetsDTO result = new PetsDTO(vetService.getVetPatients(id).stream()
                .map(pet -> new PetDTO().encode(pet))
                .collect(Collectors.toSet()));
        log.trace("getVetPatients --- method finished: result={}", result);
        return result;
    }

    @RequestMapping(value = "/vets", method = RequestMethod.POST)
    void addVet(@RequestBody VetDTO vetDTO) {
        log.trace("addVet --- method entered: vetDTO={}", vetDTO);
        vetService.addVet(vetDTO.getFirstName(), vetDTO.getLastName(), vetDTO.getEmail(), vetDTO.getPhoneNumber(),
                vetDTO.getDateOfBirth(), vetDTO.getSalary(), vetDTO.getRating());
        log.trace("addVet --- method finished");
    }

    @RequestMapping(value = "/vets/{id}", method = RequestMethod.DELETE)
    void deleteVet(@PathVariable Long id) {
        log.trace("deleteVet --- method entered: id={}", id);
        vetService.deleteVet(id);
        log.trace("deleteVet --- method finished");
    }

    @RequestMapping(value = "/vets/{id}", method = RequestMethod.PUT)
    void updateVet(@PathVariable Long id, @RequestBody VetDTO vetDTO) {
        log.trace("updateVet --- method entered: id={}, vetDTO={}", id, vetDTO);
        vetService.updateVet(id, vetDTO.getFirstName(), vetDTO.getLastName(), vetDTO.getEmail(), vetDTO.getPhoneNumber(),
                vetDTO.getDateOfBirth(), vetDTO.getSalary(), vetDTO.getRating());
        log.trace("updateVet --- method finished");
    }
}
