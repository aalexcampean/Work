package web.controller;

import core.dto.OwnerDTO;
import core.dto.PetDTO;
import core.dto.collections.OwnersDTO;
import core.dto.collections.PetsDTO;
import core.entity.Owner;
import core.entity.Pet;
import core.service.interfaces.IOwnerService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.stream.Collectors;

@RestController
public class OwnerController {
    // Logger
    public static final Logger log = LoggerFactory.getLogger(OwnerController.class);
    // Dependencies
    @Autowired
    private IOwnerService ownerService;

    @RequestMapping(value = "/owners")
    OwnersDTO getOwners() {
        log.trace("getOwners --- method started");
        OwnersDTO result = new OwnersDTO(ownerService.getOwners()
                .stream()
                .map(owner -> new OwnerDTO().encode(owner))
                .collect(Collectors.toSet()));
        log.trace("getOwners --- method finished: result={}", result);
        return result;
    }

    @RequestMapping(value = "/owners/pageNumber={pageNumber}&pageSize={pageSize}")
    OwnersDTO getPaginatedOwners(@PathVariable int pageNumber, @PathVariable int pageSize) {
        log.trace("getPaginatedOwners --- method started");
        List<Owner> owners = ownerService.getOwners();
        Integer total = owners.size();
        if (pageSize != -1) {
            owners = owners.stream().skip((long) pageNumber * pageSize).limit(pageSize).collect(Collectors.toList());
        }
        OwnersDTO result = new OwnersDTO(owners.stream().map(owner -> new OwnerDTO().encode(owner)).collect(Collectors.toSet()), total);
        log.trace("getPaginatedOwners --- method finished: result={}", result);
        return result;
    }

    @RequestMapping(value = "/owners/pets/{id}")
    PetsDTO getOwnerPets(@PathVariable Long id) {
        log.trace("getOwnerPets --- method started");
        PetsDTO result = new PetsDTO(ownerService.getOwnerPets(id)
                .stream()
                .map(pet -> new PetDTO().encode(pet))
                .collect(Collectors.toSet()));
        log.trace("getOwnerPets --- method finished: result={}", result);
        return result;
    }

    @RequestMapping(value = "/owners", method = RequestMethod.POST)
    void addOwner(@RequestBody OwnerDTO ownerDTO) {
        log.trace("addOwner --- method entered: ownerDTO={}", ownerDTO);
        ownerService.addOwner(ownerDTO.getFirstName(), ownerDTO.getLastName(), ownerDTO.getEmail(),
                ownerDTO.getPhoneNumber(), ownerDTO.getDateOfBirth());
        log.trace("addOwner --- method finished");
    }

    @RequestMapping(value = "/owners/{id}", method = RequestMethod.DELETE)
    void deleteOwner(@PathVariable Long id) {
        log.trace("deleteOwner --- method entered: id={}", id);
        ownerService.deleteOwner(id);
        log.trace("deleteOwner --- method finished");
    }

    @RequestMapping(value = "/owners/{id}", method = RequestMethod.PUT)
    void updateOwner(@PathVariable Long id, @RequestBody OwnerDTO ownerDTO) {
        log.trace("updateOwner --- method entered: id={}, ownerDTO={}", id, ownerDTO);
        ownerService.updateOwner(id, ownerDTO.getFirstName(), ownerDTO.getLastName(), ownerDTO.getEmail(),
                ownerDTO.getPhoneNumber(), ownerDTO.getDateOfBirth());
        log.trace("updateOwner --- method finished");
    }
}
