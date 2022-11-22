package core.service.interfaces;

import core.entity.BirthCertificate;

import java.util.List;

public interface IBirthCertificateService {
    List<BirthCertificate> getBirthCertificates();

    void addBirthCertificate(String text, String location, String date, Integer healthGrade, Long petId);
    void deleteBirthCertificate(Long id);
    void updateBirthCertificate(Long id, String text, String location, String date, Integer healthGrade, Long petId);
}
