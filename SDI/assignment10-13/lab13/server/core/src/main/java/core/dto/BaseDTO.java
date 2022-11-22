package core.dto;

import lombok.*;

import java.io.Serializable;

@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
@ToString
public abstract class BaseDTO<DTO, Entity> implements Serializable {
    private Long id;

    public abstract DTO encode(Entity entity);
}