package Common.Model.Domain;

import java.util.*;
import java.util.stream.Stream;

public class Vet extends BaseEntity<Long> {
    private String firstName;
    private String lastName;
    private String email;
    private String phoneNumber;
    private String dateOfBirth;
    private int salary;
    private int rating;

    public Vet(){}

    public Vet(long id, String firstName, String lastName, String email, String phoneNumber, String dateOfBirth, int salary ,int rating) {
        super.setId(id);
        this.firstName = firstName;
        this.lastName = lastName;
        this.email = email;
        this.phoneNumber = phoneNumber;
        this.dateOfBirth = dateOfBirth;
        this.salary = salary;
        this.rating = rating;
    }

    public String getFirstName() {return firstName;}
    public void setFirstName(String firstName) {this.firstName = firstName;}

    public String getLastName() {return lastName;}
    public void setLastName(String lastName) {this.lastName = lastName;}

    public String getEmail() {return email;}
    public void setEmail(String email) {this.email = email;}

    public String getPhoneNumber() {return phoneNumber;}
    public void setPhoneNumber(String phoneNumber) {this.phoneNumber = phoneNumber;}

    public String getDateOfBirth() {return dateOfBirth;}
    public void setDateOfBirth(String dateOfBirth) {this.dateOfBirth = dateOfBirth;}

    public int getSalary() {return salary;}
    public void setSalary(int salary) {this.salary = salary;}

    public int getRating() {return rating;}
    public void setRating(int rating) {this.rating = rating;}

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Vet)) return false;
        Vet vet = (Vet) o;
        return salary == vet.getSalary()
                && rating == vet.getRating()
                && firstName.equals(vet.getFirstName())
                && lastName.equals(vet.getLastName())
                && email.equals(vet.getEmail())
                && phoneNumber.equals(vet.getPhoneNumber())
                && dateOfBirth.equals(vet.getDateOfBirth());
    }

    @Override
    public int hashCode() {
        return Objects.hash(firstName, lastName, email, phoneNumber, dateOfBirth, salary, rating);
    }

    @Override
    public String toString() {
        return "Vet{" +
                "firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                ", email='" + email + '\'' +
                ", phoneNumber='" + phoneNumber + '\'' +
                ", dateOfBirth='" + dateOfBirth + '\'' +
                ", salary=" + salary +
                ", rating=" + rating +
                '}' + super.toString();
    }

    public String encode() {
        // Get the Set of String
        List<String> attributeList = Arrays.asList(String.valueOf(super.getId()),
                firstName, lastName, email, phoneNumber, dateOfBirth, String.valueOf(salary), String.valueOf(rating));

        // Convert the Set of String to String
        return String.join(",", attributeList);
    }

    public static Vet decode(String data) {
        // \s* any number of whitespace characters
        //  a comma
        // \s* any number of whitespace characters
        List<String> attributeList = Stream.of(data.trim().split("\\s*,\\s*")).toList();

        Long id = Long.parseLong(attributeList.get(0));
        String firstName = attributeList.get(1);
        String lastName = attributeList.get(2);
        String email = attributeList.get(3);
        String phoneNumber = attributeList.get(4);
        String dateOfBirth = attributeList.get(5);
        Integer salary = Integer.parseInt(attributeList.get(6));
        Integer rating = Integer.parseInt(attributeList.get(7));

        return new Vet(id, firstName, lastName, email, phoneNumber, dateOfBirth, salary, rating);
    }
}
