package core.dto.collections;

import core.dto.BirthCertificateDTO;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.Set;

@NoArgsConstructor
@AllArgsConstructor
@Data
public class BirthCertificatesDTO {
    private Set<BirthCertificateDTO> birthCertificates;
}
