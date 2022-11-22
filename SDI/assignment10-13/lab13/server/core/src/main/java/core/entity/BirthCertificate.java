package core.entity;

import lombok.*;
import org.hibernate.Hibernate;

import javax.persistence.*;
import javax.validation.constraints.Size;
import java.util.Objects;

@Entity
@NoArgsConstructor
@RequiredArgsConstructor
@Getter
@Setter
@ToString(callSuper = true)
public class BirthCertificate extends BaseEntity<Long> {
    @NonNull
    @Size(min = 1, max = 50)
    private String text;

    @NonNull
    @Size(min = 1, max = 50)
    private String location;

    @NonNull
    @Size(min = 10, max = 10)
    private String date;

    @NonNull
    private Integer healthGrade;

    @NonNull
    @OneToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "petId")
    private Pet pet;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || Hibernate.getClass(this) != Hibernate.getClass(o)) return false;
        BirthCertificate that = (BirthCertificate) o;
        return getId() != null && Objects.equals(getId(), that.getId());
    }

    @Override
    public int hashCode() {
        return getClass().hashCode();
    }
}
