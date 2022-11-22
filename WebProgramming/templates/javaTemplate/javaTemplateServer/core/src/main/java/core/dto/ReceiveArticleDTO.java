package core.dto;

import lombok.*;

@NoArgsConstructor
@AllArgsConstructor
@Data
@Getter
@Setter
@EqualsAndHashCode
@ToString(callSuper = true)
public class ReceiveArticleDTO {
    private String userName;
    private String summary;
    private String journalName;
}
