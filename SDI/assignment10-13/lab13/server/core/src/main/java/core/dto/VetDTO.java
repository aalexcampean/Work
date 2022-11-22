package core.dto;

import core.entity.Vet;
import lombok.*;

@NoArgsConstructor
@AllArgsConstructor
@Data
@Getter
@Setter
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
public class VetDTO extends BaseDTO<VetDTO, Vet> {
    private String firstName;
    private String lastName;
    private String email;
    private String phoneNumber;
    private String dateOfBirth;
    private Integer salary;
    private Integer rating;

    @Override
    public VetDTO encode(Vet vet) {
        VetDTO vetDTO = new VetDTO(vet.getFirstName(),
                vet.getLastName(),
                vet.getEmail(),
                vet.getPhoneNumber(),
                vet.getDateOfBirth(),
                vet.getSalary(),
                vet.getRating());
        vetDTO.setId(vet.getId());
        return vetDTO;
    }
}
