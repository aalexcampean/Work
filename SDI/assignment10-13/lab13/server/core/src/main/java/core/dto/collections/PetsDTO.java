package core.dto.collections;

import core.dto.PetDTO;
import core.dto.VetDTO;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.Set;

@NoArgsConstructor
@AllArgsConstructor
@Data
public class PetsDTO {
    private Set<PetDTO> pets;
    Integer total = null;

    public PetsDTO(Set<PetDTO> pets) {
        this.pets = pets;
    }
}
