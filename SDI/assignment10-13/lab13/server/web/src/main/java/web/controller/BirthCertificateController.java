package web.controller;

import core.dto.BirthCertificateDTO;
import core.dto.collections.BirthCertificatesDTO;
import core.service.interfaces.IBirthCertificateService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.stream.Collectors;

@RestController
public class BirthCertificateController {
    // Logger
    public static final Logger log = LoggerFactory.getLogger(PetController.class);
    // Dependencies
    @Autowired
    private IBirthCertificateService birthCertificateService;

    @RequestMapping(value = "/birthCertificates")
    BirthCertificatesDTO getBirthCertificates() {
        log.trace("getBirthCertificates --- method started");
        BirthCertificatesDTO result = new BirthCertificatesDTO(birthCertificateService.getBirthCertificates()
                .stream()
                .map(birthCertificate -> new BirthCertificateDTO().encode(birthCertificate))
                .collect(Collectors.toSet()));
        log.trace("getBirthCertificates --- method finished: result={}", result);
        return result;
    }

    @RequestMapping(value = "/birthCertificates", method = RequestMethod.POST)
    void addBirthCertificate(@RequestBody BirthCertificateDTO birthCertificateDTO) {
        log.trace("addBirthCertificate --- method entered: birthCertificateDTO={}", birthCertificateDTO);
        birthCertificateService.addBirthCertificate(birthCertificateDTO.getText(), birthCertificateDTO.getLocation(), birthCertificateDTO.getDate(), birthCertificateDTO.getHealthGrade(), birthCertificateDTO.getPetId());
        log.trace("addBirthCertificate --- method finished");
    }

    @RequestMapping(value = "/birthCertificates/{id}", method = RequestMethod.DELETE)
    void deleteBirthCertificate(@PathVariable Long id) {
        log.trace("deleteBirthCertificate --- method entered: id={}", id);
        birthCertificateService.deleteBirthCertificate(id);
        log.trace("deleteBirthCertificate --- method finished");
    }

    @RequestMapping(value = "/birthCertificates/{id}", method = RequestMethod.PUT)
    void updateBirthCertificate(@PathVariable Long id, @RequestBody BirthCertificateDTO birthCertificateDTO) {
        log.trace("updateBirthCertificate --- method entered: id={}, birthCertificateDTO={}", id, birthCertificateDTO);
        birthCertificateService.updateBirthCertificate(id, birthCertificateDTO.getText(), birthCertificateDTO.getLocation(), birthCertificateDTO.getDate(), birthCertificateDTO.getHealthGrade(), birthCertificateDTO.getPetId());
        log.trace("updateBirthCertificate --- method finished");
    }
}
