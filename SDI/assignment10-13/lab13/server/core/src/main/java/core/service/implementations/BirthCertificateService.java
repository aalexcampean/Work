package core.service.implementations;

import core.entity.*;
import core.repository.IBirthCertificateRepository;
import core.repository.IPetRepository;
import core.service.interfaces.IBirthCertificateService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.security.cert.Certificate;
import java.util.List;

@Service
public class BirthCertificateService implements IBirthCertificateService {
    // Logger
    public static final Logger log = LoggerFactory.getLogger(PetService.class);
    // Dependencies
    @Autowired
    private IBirthCertificateRepository birthCertificateRepository;
    @Autowired
    private IPetRepository petRepository;

    @Override
    @Transactional
    public List<BirthCertificate> getBirthCertificates() {
        log.trace("getBirthCertificates --- method started");
        List<BirthCertificate> result = birthCertificateRepository.findAll();
        log.trace("getBirthCertificates --- method finished: result={}", result);
        return result;
    }

    @Override
    @Transactional
    public void addBirthCertificate(String text, String location, String date, Integer healthGrade, Long petId) {
        log.trace("addBirthCertificate --- method started: text={}, location={}, date={}, healthGrade={}, petId={}", text, location, date, healthGrade, petId);
        Pet pet = petRepository.findById(petId).orElseThrow(() -> new ClinicException("Pet doesn't exist"));
        BirthCertificate birthCertificate = new BirthCertificate(text, location, date, healthGrade, pet);
        birthCertificateRepository.save(birthCertificate);
        log.debug("addBirthCertificate --- added: birthCertificate={}", birthCertificate);
        log.trace("addBirthCertificate --- method finished");
    }

    @Override
    @Transactional
    public void deleteBirthCertificate(Long id) {
        log.trace("deleteBirthCertificate --- method started: id={}", id);
        birthCertificateRepository.findById(id).ifPresentOrElse(birthCertificate -> {
            birthCertificate.getPet().setBirthCertificate(null);
            birthCertificateRepository.deleteById(id);
            birthCertificateRepository.flush();
            log.debug("deleteBirthCertificate --- deleted: birthCertificate={}", birthCertificate);
        }, () -> {
            throw new ClinicException("Certificate does not exist");
        });
        log.trace("deleteBirthCertificate --- method finished");
    }

    @Override
    @Transactional
    public void updateBirthCertificate(Long id, String text, String location, String date, Integer healthGrade, Long petId) {
        log.trace("updateBirthCertificate --- method started: id={}, text={}, location={}, date={}, healthGrade={}", id, text, location, date, healthGrade);
        birthCertificateRepository.findById(id).ifPresentOrElse(birthCertificate -> {
            Pet newPet = petRepository.findById(petId).orElseThrow(() -> new ClinicException("Pet doesn't exist"));
            birthCertificate.setText(text);
            birthCertificate.setLocation(location);
            birthCertificate.setDate(date);
            birthCertificate.setHealthGrade(healthGrade);
            birthCertificate.setPet(newPet);
            birthCertificate.getPet().setBirthCertificate(null);
            log.debug("updateBirthCertificate --- updated: birthCertificate={}", birthCertificate);
        }, () -> {
            throw new ClinicException("Birth certificate does not exist");
        });
        log.trace("updateBirthCertificate --- method finished");
    }
}
