package ro.ubb.catalog.Domain;

import java.time.LocalDate;

public class VetContract extends BaseEntity<Long> {
    private int vetID;
    private int clinicID;
    private LocalDate contractDate;

    public VetContract(int vetID, int clinicID, LocalDate contractDate) {
        this.vetID = vetID;
        this.clinicID = clinicID;
        this.contractDate = contractDate;
    }

    public int getVetID() {
        return vetID;
    }

    public void setVetID(int vetID) {
        this.vetID = vetID;
    }

    public int getClinicID() {
        return clinicID;
    }

    public void setClinicID(int clinicID) {
        this.clinicID = clinicID;
    }

    public LocalDate getContractDate() {
        return contractDate;
    }

    public void setContractDate(LocalDate contractDate) {
        this.contractDate = contractDate;
    }

    @Override
    public String toString() {
        return "VetContract{ " +
                "VetContractID=" + getId() +
                ", VetID=" + vetID +
                ", ClinicID=" + clinicID +
                ", ContractDate=" + contractDate +
                '}';
    }

    @Override
    public int hashCode() {
        int result = clinicID;
        result = 31 * result + clinicID;
        result = 31 * result + contractDate.hashCode();
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if(this == obj)
            return true;
        if(obj == null || getClass() != obj.getClass())
            return false;

        VetContract vc = (VetContract) obj;
        if(vc.vetID != vetID) return false;
        if(vc.clinicID != clinicID) return false;
        return (contractDate == vc.contractDate);
    }
}
