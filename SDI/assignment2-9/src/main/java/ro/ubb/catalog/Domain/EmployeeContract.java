package ro.ubb.catalog.Domain;
import java.time.LocalDate;

/**
 * @author liviu
 */

public class EmployeeContract extends BaseEntity<Long> {

    private LocalDate date;
    private int EmployeeID;
    private int ClinicID;
    

    public EmployeeContract() {
    }

    public EmployeeContract(LocalDate date, int EmployeeID, int ClinicID) {
        this.date = date;
        this.EmployeeID = EmployeeID;
        this.ClinicID = ClinicID;
    }

    public LocalDate getDate() {
        return this.date;
    }

    public void setDate(LocalDate date) {
        this.date = date;
    }

    public int getEmployeeID() {
        return this.EmployeeID;
    }

    public void setEmployeeID(int EmployeeID) {
        this.EmployeeID = EmployeeID;
    }

    public int getClinicID() {
        return this.ClinicID;
    }

    public void setClinicID(int ClinicID) {
        this.ClinicID = ClinicID;
    }

    @Override
    public int hashCode() {
        int result = ClinicID;
        result = 31 * result + EmployeeID;
        result = 31 * result + date.hashCode();
        return result;
    }
    

    @Override
    public boolean equals(Object o){
        if(this == o) return true;
        if(o == null || getClass() != o.getClass()) return false;

        EmployeeContract ec = (EmployeeContract) o;
        if(ec.EmployeeID != EmployeeID) return false;
        if(ec.ClinicID != ClinicID) return false;
        return (date == ec.date);
    }

    @Override
    public String toString() {
        return "EmployeeContract{" +
                "EmployeeID=" + EmployeeID +
                ", ClinicID=" + ClinicID +
                ", date=" + date +
                '}';
    }
}
