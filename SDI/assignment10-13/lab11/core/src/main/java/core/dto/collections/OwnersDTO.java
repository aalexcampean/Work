package core.dto.collections;

import core.dto.OwnerDTO;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.Set;

@NoArgsConstructor
@AllArgsConstructor
@Data
public class OwnersDTO {
    private Set<OwnerDTO> owners;
}
