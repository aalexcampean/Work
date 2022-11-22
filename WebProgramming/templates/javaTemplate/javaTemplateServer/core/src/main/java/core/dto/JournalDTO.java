package core.dto;

import core.entity.Journal;
import lombok.*;

@NoArgsConstructor
@AllArgsConstructor
@Data
@Getter
@Setter
@EqualsAndHashCode
@ToString(callSuper = true)
public class JournalDTO {
    private int id;
    private String name;

    public JournalDTO encode(Journal journal) {
        return new JournalDTO(journal.getId(),
                journal.getName());
    }
}
