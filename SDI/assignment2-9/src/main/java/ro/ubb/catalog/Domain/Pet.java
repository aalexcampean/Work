package ro.ubb.catalog.Domain;

public class Pet extends BaseEntity<Long>{

    private String species;
    private String breed;
    private String petName;
    private int personId;

    public Pet() {
    }

    public Pet( String species, String breed, String petName, int personId) {

        this.species = species;
        this.breed = breed;
        this.petName = petName;
        this.personId = personId;
    }

    public String getSpecies() {
        return species;
    }

    public void setSpecies(String species) {
        this.species = species;
    }

    public String getBreed() {
        return breed;
    }

    public void setBreed(String breed) {
        this.breed = breed;
    }

    public String getPetName() {
        return petName;
    }

    public void setPetName(String petName) {
        this.petName = petName;
    }

    public int getPersonId() { return personId; }

    public void setPersonId(int personId) {this.personId = personId; }



    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Pet pet = (Pet) o;


        if (!species.equals(pet.species)) return false;
        if (!breed.equals(pet.breed)) return false;
        if (!petName.equals(pet.petName)) return false;
        return personId != pet.personId;

    }

    @Override
    public int hashCode() {
        int result =  species.hashCode();
        result = 31 * result + breed.hashCode();
        result = 31 * result + petName.hashCode();
        result = 31 * result + personId;
        return result;
    }

    @Override
    public String toString() {
        return "Pet {" +

                " species='" + species + '\'' +
                ", breed='" + breed + '\'' +
                ", petName='" + petName + '\'' +
                ", personId=" + personId +
                "} " + super.toString();
    }
}
