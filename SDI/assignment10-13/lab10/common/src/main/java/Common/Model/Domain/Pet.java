package Common.Model.Domain;

import java.util.*;
import java.util.stream.Stream;

public class Pet extends BaseEntity<Long>{
    private String species;
    private String breed;
    private String name;
    private String dateOfEnrolment;
    private long personId;

    public Pet(){}

    public Pet(long id, String species, String breed, String name, String dateOfEnrolment, long personId) {
        super.setId(id);
        this.species = species;
        this.breed = breed;
        this.name = name;
        this.dateOfEnrolment = dateOfEnrolment;
        this.personId = personId;
    }

    public String getSpecies() {return species;}
    public void setSpecies(String species) {this.species = species;}

    public String getBreed() {return breed;}
    public void setBreed(String breed) {this.breed = breed;}

    public String getName() {return name;}
    public void setName(String name) {this.name = name;}

    public String getDateOfEnrolment() {return dateOfEnrolment;}
    public void setDateOfEnrolment(String dateOfEnrolment) {this.dateOfEnrolment = dateOfEnrolment;}

    public long getPersonId() {return personId;}
    public void setPersonId(long personId) {this.personId = personId;}

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Pet)) return false;
        Pet pet = (Pet) o;
        return personId == pet.getPersonId()
                && species.equals(pet.getSpecies())
                && breed.equals(pet.getBreed())
                && name.equals(pet.getName())
                && dateOfEnrolment.equals(pet.getDateOfEnrolment());
    }

    @Override
    public int hashCode() {
        return Objects.hash(species, breed, name, dateOfEnrolment, personId);
    }

    @Override
    public String toString() {
        return "Pet{" +
                "species='" + species + '\'' +
                ", breed='" + breed + '\'' +
                ", name='" + name + '\'' +
                ", dateOfEnrolment='" + dateOfEnrolment + '\'' +
                ", personId=" + personId +
                '}' + super.toString();
    }

    public String encode() {
        // Get the Set of String
        List<String> attributeList = Arrays.asList(String.valueOf(super.getId()),
                species, breed, name, dateOfEnrolment, String.valueOf(personId));

        // Convert the Set of String to String
        return String.join(",", attributeList);
    }

    public static Pet decode(String data) {
        // \s* any number of whitespace characters
        //  a comma
        // \s* any number of whitespace characters
        List<String> attributeList = Stream.of(data.trim().split("\\s*,\\s*")).toList();

        Long id = Long.parseLong(attributeList.get(0));
        String species = attributeList.get(1);
        String breed = attributeList.get(2);
        String name = attributeList.get(3);
        String dateOfEnrolment = attributeList.get(4);
        Long personId = Long.parseLong(attributeList.get(5));

        return new Pet(id, species, breed, name, dateOfEnrolment, personId);
    }
}
