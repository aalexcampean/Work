package Common.Model.Domain;

import java.util.*;
import java.util.stream.Stream;

public class Appointment extends BaseEntity<Long> {
    private long petId;
    private long vetId;
    private String type;
    private String date;

    public Appointment(){}

    public Appointment(long id, long petId, long vetId, String type, String date) {
        super.setId(id);
        this.petId = petId;
        this.vetId = vetId;
        this.type = type;
        this.date = date;
    }

    public long getPetId() {return petId;}
    public void setPetId(long petId) {this.petId = petId;}

    public long getVetId() {return vetId;}
    public void setVetId(long vetId) {this.vetId = vetId;}

    public String getType() {return type;}
    public void setType(String type) {this.type = type;}

    public String getDate() {return date;}
    public void setDate(String date) {this.date = date;}

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Appointment)) return false;
        Appointment appointment = (Appointment) o;
        return petId == appointment.getPetId()
                && vetId == appointment.getVetId()
                && type.equals(appointment.getType())
                && date.equals(appointment.getDate());
    }

    @Override
    public int hashCode() {
        return Objects.hash(petId, vetId, type, date);
    }

    @Override
    public String toString() {
        return "Appointment{" +
                "petId=" + petId +
                ", vetId=" + vetId +
                ", type='" + type + '\'' +
                ", date='" + date + '\'' +
                '}' + super.toString();
    }

    public String encode() {
        // Get the Set of String
        List<String> attributeList = Arrays.asList(String.valueOf(super.getId()),
                String.valueOf(petId), String.valueOf(vetId), type, date);

        // Convert the Set of String to String
        return String.join(",", attributeList);
    }

    public static Appointment decode(String data) {
        // \s* any number of whitespace characters
        //  a comma
        // \s* any number of whitespace characters
        List<String> attributeList = Stream.of(data.trim().split("\\s*,\\s*")).toList();

        Long id = Long.parseLong(attributeList.get(0));
        Long petId = Long.parseLong(attributeList.get(1));
        Long vetId = Long.parseLong(attributeList.get(2));
        String type = attributeList.get(3);
        String date = attributeList.get(4);

        return new Appointment(id, petId, vetId, type, date);
    }
}
