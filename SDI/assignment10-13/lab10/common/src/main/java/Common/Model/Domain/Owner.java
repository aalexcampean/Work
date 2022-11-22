package Common.Model.Domain;

import java.util.*;
import java.util.stream.Stream;

public class Owner extends BaseEntity<Long> {
    private String firstName;
    private String lastName;
    private String email;
    private String phoneNumber;
    private String dateOfBirth;

    public Owner(){}

    public Owner(long id, String firstName, String lastName, String email, String phoneNumber, String dateOfBirth) {
        super.setId(id);
        this.firstName = firstName;
        this.lastName = lastName;
        this.email = email;
        this.phoneNumber = phoneNumber;
        this.dateOfBirth = dateOfBirth;
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

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Owner)) return false;
        Owner owner = (Owner) o;
        return firstName.equals(owner.getFirstName())
                && lastName.equals(owner.getLastName())
                && email.equals(owner.getEmail())
                && phoneNumber.equals(owner.getPhoneNumber())
                && dateOfBirth.equals(owner.getDateOfBirth());
    }

    @Override
    public int hashCode() {
        return Objects.hash(firstName, lastName, email, phoneNumber, dateOfBirth);
    }

    @Override
    public String toString() {
        return "Owner{" +
                "firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                ", email='" + email + '\'' +
                ", phoneNumber='" + phoneNumber + '\'' +
                ", dateOfBirth='" + dateOfBirth + '\'' +
                '}' + super.toString();
    }

    public String encode() {
        // Get the Set of String
        List<String> attributeList = Arrays.asList(String.valueOf(super.getId()),
                firstName, lastName, email, phoneNumber, dateOfBirth);

        // Convert the Set of String to String
        return String.join(",", attributeList);
    }

    public static Owner decode(String data) {
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

        return new Owner(id, firstName, lastName, email, phoneNumber, dateOfBirth);
    }
}
