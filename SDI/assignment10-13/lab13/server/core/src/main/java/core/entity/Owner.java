package core.entity;

import lombok.*;
import org.hibernate.Hibernate;

import javax.persistence.CascadeType;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.OneToMany;
import javax.validation.constraints.Size;
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

@Entity
@NoArgsConstructor
@RequiredArgsConstructor
@Getter
@Setter
@ToString(callSuper = true)
public class Owner extends BaseEntity<Long> {
    @NonNull
    @Size(min = 2, max = 50)
    private String firstName;

    @NonNull
    @Size(min = 2, max = 50)
    private String lastName;

    @NonNull
    @Size(min = 2, max = 50)
    private String email;

    @NonNull
    @Size(min = 10, max = 10)
    private String phoneNumber;

    @NonNull
    @Size(min = 10, max = 10)
    private String dateOfBirth;

    @OneToMany(mappedBy = "owner", cascade = CascadeType.ALL, fetch = FetchType.EAGER, orphanRemoval = true)
    @ToString.Exclude
    private Set<Pet> pets = new HashSet<>();

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || Hibernate.getClass(this) != Hibernate.getClass(o)) return false;
        Owner owner = (Owner) o;
        return getId() != null && Objects.equals(getId(), owner.getId());
    }

    @Override
    public int hashCode() {
        return getClass().hashCode();
    }
}