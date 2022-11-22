package ro.ubb.catalog.Domain;

public class Surgery extends BaseEntity<Long> {
    private int petId;
    private int vetId;
    private String surgeryDate;
    private String surgeryType;

    // constructors
    public Surgery() {

    }

    public Surgery(int petId, int vetId, String surgeryDate, String surgeryType) {
        this.petId = petId;
        this.vetId = vetId;
        this.surgeryDate = surgeryDate;
        this.surgeryType = surgeryType;
    }

    // getters
    public int getPetId() {
        return this.petId;
    }
    public int getVetId() {
        return this.vetId;
    }
    public String getSurgeryDate() {
        return this.surgeryDate;
    }
    public String getSurgeryType() {
        return this.surgeryType;
    }

    // setters
    public void setPetId(int newPetId) {
        this.petId = newPetId;
    }
    public void setVetId(int newVetId) {
        this.vetId = newVetId;
    }
    public void setSurgeryDate(String newSurgeryDate) {
        this.surgeryDate = newSurgeryDate;
    }
    public void setSurgeryType(String newSurgeryType) {
        this.surgeryType = newSurgeryType;
    }

    @Override
    public boolean equals(Object o) {
        if(this == o)
            return true;
        if(o == null || getClass() != o.getClass())
            return false;

        Surgery surgery = (Surgery) o;

        if(petId != surgery.petId)
            return false;
        if(vetId != surgery.vetId)
            return false;
        if(!surgeryDate.equals(surgery.surgeryDate))
            return false;
        return surgeryType.equals(surgery.surgeryType);
    }

    // hashing
    @Override
    public int hashCode() {
        int result = petId;
        result = 31 * result + vetId;
        result = 31 * result + surgeryDate.hashCode();
        result = 31 * result + surgeryType.hashCode();
        return result;
    }

    // string representation
    @Override
    public String toString() {
        return "Surgery {" +
                "pet id='" + petId + '\'' +
                ", vet id='" + vetId + '\'' +
                ", surgery date='" + surgeryDate + '\'' +
                ", surgery type=" + surgeryType +
                "} " + super.toString();
    }
}
