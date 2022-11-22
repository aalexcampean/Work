package web.controller;

import core.dto.AppointmentDTO;
import core.dto.OwnerDTO;
import core.dto.PetDTO;
import core.dto.VetDTO;
import core.dto.collections.AppointmentsDTO;
import core.dto.collections.PetsDTO;
import core.dto.collections.VetsDTO;
import core.entity.Owner;
import core.entity.Pet;
import core.entity.Vet;
import core.service.interfaces.IPetService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.stream.Collectors;

@RestController
public class PetController {
    // Logger
    public static final Logger log = LoggerFactory.getLogger(PetController.class);
    // Dependencies
    @Autowired
    private IPetService petService;

    @RequestMapping(value = "/pets")
    PetsDTO getPets() {
        log.trace("getPets --- method started");
        PetsDTO result = new PetsDTO(petService.getPets()
                .stream()
                .map(pet -> new PetDTO().encode(pet))
                .collect(Collectors.toSet()));
        log.trace("getPets --- method finished: result={}", result);
        return result;
    }

    @RequestMapping(value = "/pets/pageNumber={pageNumber}&pageSize={pageSize}")
    PetsDTO getPaginatedPets(@PathVariable int pageNumber, @PathVariable int pageSize) {
        log.trace("getPaginatedPets --- method started");
        List<Pet> pets = petService.getPets();
        Integer total = pets.size();
        if (pageSize != -1) {
            pets = pets.stream().skip((long) pageNumber * pageSize).limit(pageSize).collect(Collectors.toList());
        }
        PetsDTO result = new PetsDTO(pets.stream().map(pet -> new PetDTO().encode(pet)).collect(Collectors.toSet()), total);
        log.trace("getPaginatedPets --- method finished: result={}", result);
        return result;
    }

    @RequestMapping(value = "/pets/owner/{id}")
    OwnerDTO getPetOwner(@PathVariable Long id) {
        log.trace("getPetOwner --- method started");
        Owner owner = petService.getPetOwner(id);
        OwnerDTO result = new OwnerDTO().encode(owner);
        log.trace("getPetOwner --- method finished: result={}", result);
        return result;
    }

    @RequestMapping(value = "/pets/appointments/{id}")
    AppointmentsDTO getPetAppointments(@PathVariable Long id) {
        log.trace("getPetAppointments --- method started");
        AppointmentsDTO result = new AppointmentsDTO(petService.getPetAppointments(id).stream()
                .map(appointment -> new AppointmentDTO().encode(appointment))
                .collect(Collectors.toSet()));
        log.trace("getPetAppointments --- method finished: result={}", result);
        return result;
    }

    @RequestMapping(value = "/pets", method = RequestMethod.POST)
    void addPet(@RequestBody PetDTO petDTO) {
        log.trace("addPet --- method entered: petDTO={}", petDTO);
        petService.addPet(petDTO.getSpecies(), petDTO.getBreed(), petDTO.getName(), petDTO.getDateOfEnrolment(), petDTO.getOwnerId());
        log.trace("addPet --- method finished");
    }

    @RequestMapping(value = "/pets/{id}", method = RequestMethod.DELETE)
    void deletePet(@PathVariable Long id) {
        log.trace("deletePet --- method entered: id={}", id);
        petService.deletePet(id);
        log.trace("deletePet --- method finished");
    }

    @RequestMapping(value = "/pets/{id}", method = RequestMethod.PUT)
    void updatePet(@PathVariable Long id, @RequestBody PetDTO petDTO) {
        log.trace("updatePet --- method entered: id={}, petDTO={}", id, petDTO);
        petService.updatePet(id, petDTO.getSpecies(), petDTO.getBreed(), petDTO.getName(), petDTO.getDateOfEnrolment(), petDTO.getOwnerId());
        log.trace("updatePet --- method finished");
    }
}
