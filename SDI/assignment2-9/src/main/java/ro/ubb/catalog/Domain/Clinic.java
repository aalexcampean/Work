package ro.ubb.catalog.Domain;

public class Clinic extends BaseEntity<Long> {
    private String name;
    private String location;
    private int yearFounded;

    // Constructor
    public Clinic() {
    }

    public Clinic(String name, String location, int yearFounded) {
        this.name = name;
        this.location = location;
        this.yearFounded = yearFounded;
    }

    // Getters
    public String getName() {return name;}
    public String getLocation() {return location;}
    public int getYearFounded() {return yearFounded;}

    // Setters
    public void setName(String name) {this.name = name;}
    public void setLocation(String location) {this.location = location;}
    public void setYearFounded(int yearFounded) {this.yearFounded = yearFounded;}

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || this.getClass() != o.getClass()) return false;

        Clinic clinic = (Clinic) o;
        if (!this.name.equals(clinic.name)) return false;
        if (!this.location.equals(clinic.location)) return false;
        return this.yearFounded == clinic.yearFounded;
    }

    // HasCode Function
    @Override
    public int hashCode() {
        int result = this.name.hashCode();
        result = 31 * result + this.location.hashCode();
        result = 31 * result + this.yearFounded;
        return result;
    }

    // String Representation
    @Override
    public String toString() {
        return super.toString() + "," +
                " Clinic{" +
                " Name= " + this.name + "," +
                " Location= " + this.location + "," +
                " Year Founded= " + this.yearFounded +
                "}";
    }
}
