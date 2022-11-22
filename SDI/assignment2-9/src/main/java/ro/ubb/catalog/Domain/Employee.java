package ro.ubb.catalog.Domain;

public class Employee extends BaseEntity<Long>{

    private String firstName;
    private String lastName;
    private int salary;
    private int rating;
    private String date;

    public Employee(){

    }

    public Employee(String fn, String ln, int sal, int rat, String dt){
        this.firstName = fn;
        this.lastName = ln;
        this.salary = sal;
        this.rating = rat;
        this.date = dt;
    }

    public String getFirstName(){
        return this.firstName;
    }

    public String getLastName(){
        return this.lastName;
    }

    public String getDate(){
        return this.date;
    }

    public int getSalary(){
        return this.salary;
    }

    public int getRating(){
        return this.rating;
    }

    public void setFirstName(String fn){
        this.firstName = fn;
    }

    public void setLastName(String ln){
        this.lastName=  ln;
    }

    public void setSalary(int sal){
        this.salary = sal;
    }

    public void setRating(int rat){
        this.rating = rat;
    }

    public void setDate(String dt){
        this.date = dt;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Employee employee = (Employee) o;


        if (!firstName.equals(employee.firstName)) return false;
        if (!lastName.equals(employee.lastName)) return false;
        if (!date.equals(employee.date)) return false;
        if (salary != employee.salary) return false;
        return rating != employee.rating;
    }

    @Override
    public int hashCode() {
        int result = firstName.hashCode();
        result = 31 * result + lastName.hashCode();
        result = 31 * result + salary;
        result = 31 * result + rating;
        result = 31 * result + date.hashCode();
        return result;
    }

    @Override
    public String toString() {
        return "Employee {" +
                " firstName= '" + firstName + '\'' +
                ", lastName= '" + lastName + '\'' +
                ", salary= " + salary + '\'' +
                ", rating= " + rating +'\'' +
                ", date= " + date +
                "} " + super.toString();
    }
}
