package ro.ubb.catalog.Domain;

public class Vet extends ro.ubb.catalog.Domain.BaseEntity<Long> {

    private String firstName;
    private String lastName;
    private int salary;
    private int rating;
    private String date;

    public Vet(){

    }

    public Vet( String fn, String ln, int sal,int rate, String d){

        this.firstName=fn;
        this.lastName=ln;
        this.salary=sal;
        this.rating=rate;
        this.date=d;
    }


    public String getFirstName(){return this.firstName;}
    public String getLastName(){return this.lastName;}
    public int getSalary(){return this.salary;}
    public int getRating(){return this.rating;}
    public String getDate(){return this.date;}


    public void setFirstName(String fn){this.firstName=fn;}
    public void setLastName(String ln){this.lastName=ln;}
    public void setSalary(int sal){this.salary=sal;}
    public void setRating(int rating){this.rating=rating;}
    public void setDate(String date){this.date=date;}

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Vet vet = (Vet) o;


        if (!firstName.equals(vet.firstName)) return false;
        if (!lastName.equals(vet.lastName)) return false;
        if (!date.equals(vet.date)) return false;
        if (salary != vet.salary) return false;
        return rating != vet.rating;

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
        return "Vet {" +
                " first name= '" + firstName + '\'' +
                ", last_name= '" + lastName + '\'' +
                ", salary= " + salary + '\'' +
                ", rating= " + rating +'\'' +
                ", date= " + date +
                "} " + super.toString();
    }


}
