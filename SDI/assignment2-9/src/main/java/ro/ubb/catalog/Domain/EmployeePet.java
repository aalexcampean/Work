package ro.ubb.catalog.Domain;

public class EmployeePet extends BaseEntity<Long> {
    private int employeeId;
    private int petId;
    private String typeOfAction;
    private String date;

    // constructors
    public EmployeePet() {

    }

    public EmployeePet(int employeeId, int petId, String typeOfAction, String date) {
        this.employeeId = employeeId;
        this.petId = petId;
        this.typeOfAction = typeOfAction;
        this.date = date;
    }

    // getters
    public int getEmployeeId() {
        return this.employeeId;
    }
    public int getPetId() {
        return this.petId;
    }
    public String getTypeOfAction() {
        return this.typeOfAction;
    }
    public String getDate() {
        return this.date;
    }

    // setters
    public void setEmployeeId(int newEmployeeId) {
        this.employeeId = newEmployeeId;
    }
    public void setPetId(int newPetId) {
        this.petId = newPetId;
    }
    public void setTypeOfAction(String newTypeOfAction) {
        this.typeOfAction = newTypeOfAction;
    }
    public void setDate(String newDate) {
        this.date = newDate;
    }

    @Override
    public boolean equals(Object o) {
        if(this == o)
            return true;
        if(o == null || getClass() != o.getClass())
            return false;

        EmployeePet employeePet = (EmployeePet) o;

        if(employeeId != employeePet.employeeId)
            return false;
        if(petId != employeePet.petId)
            return false;
        if(!typeOfAction.equals(employeePet.typeOfAction))
            return false;
        return date.equals(employeePet.date);
    }

    // hashing
    @Override
    public int hashCode() {
        int result = employeeId;
        result = 31 * result + petId;
        result = 31 * result + typeOfAction.hashCode();
        result = 31 * result + date.hashCode();
        return result;
    }

    // string representation
    @Override
    public String toString() {
        return "EmployeePet {" +
                "employee id='" + employeeId + '\'' +
                ", pet id='" + petId + '\'' +
                ", type of action='" + typeOfAction + '\'' +
                ", date=" + date +
                "} " + super.toString();
    }
}
