package core.dto.collections;

import core.dto.VetDTO;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.Set;

@NoArgsConstructor
@AllArgsConstructor
@Data
public class VetsDTO {
    private Set<VetDTO> vets;
}
