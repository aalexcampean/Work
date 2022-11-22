package core.dto.collections;

import core.dto.OwnerDTO;
import core.dto.PetDTO;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.Set;

@NoArgsConstructor
@AllArgsConstructor
@Data
public class OwnersDTO {
    private Set<OwnerDTO> owners;
    Integer total = null;

    public OwnersDTO(Set<OwnerDTO> owners) {
        this.owners = owners;
    }
}
