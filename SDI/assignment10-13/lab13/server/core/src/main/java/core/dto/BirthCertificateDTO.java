package core.dto;

import core.entity.BirthCertificate;
import lombok.*;

@NoArgsConstructor
@AllArgsConstructor
@Data
@Getter
@Setter
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
public class BirthCertificateDTO extends BaseDTO<BirthCertificateDTO, BirthCertificate> {
    private String text;
    private String location;
    private String date;
    private Integer healthGrade;
    private long petId;

    @Override
    public BirthCertificateDTO encode(BirthCertificate birthCertificate) {
        BirthCertificateDTO birthCertificateDTO = new BirthCertificateDTO(birthCertificate.getText(),
                birthCertificate.getLocation(),
                birthCertificate.getDate(),
                birthCertificate.getHealthGrade(),
                birthCertificate.getPet().getId());
        birthCertificateDTO.setId(birthCertificate.getId());
        return birthCertificateDTO;
    }
}
