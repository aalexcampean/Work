package core.repository;

import core.entity.BirthCertificate;
import core.entity.Pet;

import java.util.List;

public interface IBirthCertificateRepository extends IBaseRepository<BirthCertificate, Long> {
    BirthCertificate findBirthCertificateByPet(Pet pet);
}
