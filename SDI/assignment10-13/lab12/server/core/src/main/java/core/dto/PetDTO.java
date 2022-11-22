package core.dto;

import core.entity.Pet;
import lombok.*;

@NoArgsConstructor
@AllArgsConstructor
@Data
@Getter
@Setter
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
public class PetDTO extends BaseDTO<PetDTO, Pet> {
    private String species;
    private String breed;
    private String name;
    private String dateOfEnrolment;
    private Long ownerId;

    @Override
    public PetDTO encode(Pet pet) {
        PetDTO petDTO = new PetDTO(pet.getSpecies(),
                pet.getBreed(),
                pet.getName(),
                pet.getDateOfEnrolment(),
                pet.getOwner().getId());
        petDTO.setId(pet.getId());
        return petDTO;
    }
}
