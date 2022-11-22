package core.dto;

import core.entity.Appointment;
import lombok.*;

@NoArgsConstructor
@AllArgsConstructor
@Data
@Getter
@Setter
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
public class AppointmentDTO extends BaseDTO<AppointmentDTO, Appointment> {
    private Long petId;
    private Long vetId;
    private String type;
    private String date;

    @Override
    public AppointmentDTO encode(Appointment appointment) {
        AppointmentDTO appointmentDTO = new AppointmentDTO(appointment.getPet().getId(),
                appointment.getVet().getId(),
                appointment.getType(),
                appointment.getDate());
        appointmentDTO.setId(appointment.getId());
        return appointmentDTO;
    }
}
