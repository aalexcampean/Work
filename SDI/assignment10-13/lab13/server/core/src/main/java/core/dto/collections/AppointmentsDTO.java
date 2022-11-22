package core.dto.collections;

import core.dto.AppointmentDTO;
import core.dto.VetDTO;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.Set;

@NoArgsConstructor
@AllArgsConstructor
@Data
public class AppointmentsDTO {
    private Set<AppointmentDTO> appointments;
    Integer total = null;

    public AppointmentsDTO(Set<AppointmentDTO> appointments) {
        this.appointments = appointments;
    }
}
