package core.dto;

import core.entity.Owner;
import lombok.*;

@NoArgsConstructor
@AllArgsConstructor
@Data
@Getter
@Setter
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
public class OwnerDTO extends BaseDTO<OwnerDTO, Owner> {
    private String firstName;
    private String lastName;
    private String email;
    private String phoneNumber;
    private String dateOfBirth;

    @Override
    public OwnerDTO encode(Owner owner) {
        OwnerDTO ownerDTO = new OwnerDTO(owner.getFirstName(),
                owner.getLastName(),
                owner.getEmail(),
                owner.getPhoneNumber(),
                owner.getDateOfBirth());
        ownerDTO.setId(owner.getId());
        return ownerDTO;
    }
}

