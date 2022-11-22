package client.ui;

import core.dto.AppointmentDTO;
import core.dto.OwnerDTO;
import core.dto.PetDTO;
import core.dto.VetDTO;
import core.dto.collections.AppointmentsDTO;
import core.dto.collections.OwnersDTO;
import core.dto.collections.PetsDTO;
import core.dto.collections.VetsDTO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import org.springframework.web.client.RestTemplate;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

@Component
public class UI {
    private final String BASE_URL = "http://localhost:8080/api";
    private final String OWNERS_URL = BASE_URL + "/owners";
    private final String PETS_URL = BASE_URL + "/pets";
    private final String VETS_URL = BASE_URL + "/vets";
    private final String APPOINTMENTS_URL = BASE_URL + "/appointments";
    @Autowired
    private RestTemplate restTemplate;

    public void menu() {
        System.out.println("0. Exit.");

        System.out.println("1. Add Owner");
        System.out.println("2. Delete Owner");
        System.out.println("3. Update Owner");
        System.out.println("4. Print All Owners");
        System.out.println("5. Print All Owner's pets");

        System.out.println("6. Add Pet");
        System.out.println("7. Delete Pet");
        System.out.println("8. Update Pet");
        System.out.println("9. Print All Pets");
        System.out.println("10. Print Pet's Owner");
        System.out.println("11. Print Pet's Appointments");

        System.out.println("12. Add Vet");
        System.out.println("13. Delete Vet");
        System.out.println("14. Update Vet");
        System.out.println("15. Print All Vets");
        System.out.println("16. Print All Vet's Patients");
        System.out.println("17. Print All Vet's Appointments");

        System.out.println("18. Add Appointment");
        System.out.println("19. Delete Appointment");
        System.out.println("20. Update Appointment");
        System.out.println("21. Print All Appointment");

        System.out.println("Choose an option: ");
    }

    public void run() {
        Scanner reader = new Scanner(System.in);
        int option;
        while (true) {
            menu();
            option = reader.nextInt();
            switch (option) {
                case 0:
                    return;
                case 1:
                    addOwnerUI();
                    break;
                case 2:
                    deleteOwnerUI();
                    break;
                case 3:
                    updateOwnerUI();
                    break;
                case 4:
                    printAllOwnersUI();
                    break;
                case 5:
                    printAllOwnerPets();
                    break;
                case 6:
                    addPetUI();
                    break;
                case 7:
                    deletePetUI();
                    break;
                case 8:
                    updatePetUI();
                    break;
                case 9:
                    printAllPetsUI();
                    break;
                case 10:
                    printPetOwnerUI();
                    break;
                case 11:
                    printPetAppointmentsUI();
                    break;
                case 12:
                    addVetUI();
                    break;
                case 13:
                    deleteVetUI();
                    break;
                case 14:
                    updateVetUI();
                    break;
                case 15:
                    printAllVetsUI();
                    break;
                case 16:
                    printAllVetPatientsUI();
                    break;
                case 17:
                    printAllVetAppointmentsUI();
                    break;
                case 18:
                    addAppointmentUI();
                    break;
                case 19:
                    deleteAppointmentUI();
                    break;
                case 20:
                    updateAppointmentUI();
                    break;
                case 21:
                    printAllAppointmentsUI();
                    break;
            }
        }
    }


    // Owner Operations

    private void addOwnerUI() {
        System.out.println("Read owner {firstName, lastName, email, phoneNumber, dateOfBirth}");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            String firstName = bufferRead.readLine();
            String lastName = bufferRead.readLine();
            String email = bufferRead.readLine();
            String phoneNumber = bufferRead.readLine();
            String dateOfBirth = bufferRead.readLine();
            OwnerDTO owner = new OwnerDTO(firstName, lastName, email, phoneNumber, dateOfBirth);

            restTemplate.postForObject(OWNERS_URL, owner, OwnerDTO.class);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void deleteOwnerUI() {
        System.out.println("Read owner id");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());

            restTemplate.delete(OWNERS_URL + "/{id}", id);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void updateOwnerUI() {
        System.out.println("Read owner {id, firstName, lastName, email, phoneNumber, dateOfBirth}");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());
            String firstName = bufferRead.readLine();
            String lastName = bufferRead.readLine();
            String email = bufferRead.readLine();
            String phoneNumber = bufferRead.readLine();
            String dateOfBirth = bufferRead.readLine();
            OwnerDTO owner = new OwnerDTO(firstName, lastName, email, phoneNumber, dateOfBirth);

            restTemplate.put(OWNERS_URL + "/{id}", owner, id);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void printAllOwnersUI() {
        OwnersDTO owners = restTemplate.getForObject(OWNERS_URL, OwnersDTO.class);
        if (owners != null && owners.getOwners() != null) {
            owners.getOwners().forEach(System.out::println);
        } else {
            System.out.println("No results");
        }
    }

    private void printAllOwnerPets() {
        System.out.println("Read owner id");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());

            PetsDTO pets = restTemplate.getForObject(OWNERS_URL + "/pets/{id}", PetsDTO.class, id);
            if (pets != null && pets.getPets() != null) {
                pets.getPets().forEach(System.out::println);
            } else {
                System.out.println("No results");
            }
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }


    // Pet Operations

    private void addPetUI() {
        System.out.println("Read pet {species, breed, name, dateOfEnrolment, ownerId}");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            String species = bufferRead.readLine();
            String breed = bufferRead.readLine();
            String name = bufferRead.readLine();
            String dateOfEnrolment = bufferRead.readLine();
            Long ownerId = Long.valueOf(bufferRead.readLine());
            PetDTO pet = new PetDTO(species, breed, name, dateOfEnrolment, ownerId);

            restTemplate.postForObject(PETS_URL, pet, PetDTO.class);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void deletePetUI() {
        System.out.println("Read pet id");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());

            restTemplate.delete(PETS_URL + "/{id}", id);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void updatePetUI() {
        System.out.println("Read pet {id, species, breed, name, dateOfEnrolment, ownerId}");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());
            String species = bufferRead.readLine();
            String breed = bufferRead.readLine();
            String name = bufferRead.readLine();
            String dateOfEnrolment = bufferRead.readLine();
            Long ownerId = Long.valueOf(bufferRead.readLine());
            PetDTO pet = new PetDTO(species, breed, name, dateOfEnrolment, ownerId);

            restTemplate.put(PETS_URL + "/{id}", pet, id);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void printAllPetsUI() {
        PetsDTO pets = restTemplate.getForObject(PETS_URL, PetsDTO.class);
        if (pets != null && pets.getPets() != null) {
            pets.getPets().forEach(System.out::println);
        } else {
            System.out.println("No results");
        }
    }

    private void printPetOwnerUI() {
        System.out.println("Read pet id");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());

            OwnerDTO owner = restTemplate.getForObject(PETS_URL + "/owner/{id}", OwnerDTO.class, id);
            System.out.println(owner);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void printPetAppointmentsUI() {
        System.out.println("Read pet id");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());

            AppointmentsDTO appointments = restTemplate.getForObject(PETS_URL + "/appointments/{id}", AppointmentsDTO.class, id);
            if (appointments != null && appointments.getAppointments() != null) {
                appointments.getAppointments().forEach(System.out::println);
            } else {
                System.out.println("No results");
            }
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }


    // Vet Operations

    private void addVetUI() {
        System.out.println("Read vet {firstName, lastName, email, phoneNumber, dateOfBirth, salary, rating}");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            String firstName = bufferRead.readLine();
            String lastName = bufferRead.readLine();
            String email = bufferRead.readLine();
            String phoneNumber = bufferRead.readLine();
            String dateOfBirth = bufferRead.readLine();
            Integer salary = Integer.parseInt(bufferRead.readLine());
            Integer rating = Integer.parseInt(bufferRead.readLine());
            VetDTO vet = new VetDTO(firstName, lastName, email, phoneNumber, dateOfBirth, salary, rating);

            restTemplate.postForObject(VETS_URL, vet, VetDTO.class);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void deleteVetUI() {
        System.out.println("Read vet id");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());

            restTemplate.delete(VETS_URL + "/{id}", id);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void updateVetUI() {
        System.out.println("Read vet {id, firstName, lastName, email, phoneNumber, dateOfBirth, salary, rating}");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());
            String firstName = bufferRead.readLine();
            String lastName = bufferRead.readLine();
            String email = bufferRead.readLine();
            String phoneNumber = bufferRead.readLine();
            String dateOfBirth = bufferRead.readLine();
            Integer salary = Integer.parseInt(bufferRead.readLine());
            Integer rating = Integer.parseInt(bufferRead.readLine());
            VetDTO vet = new VetDTO(firstName, lastName, email, phoneNumber, dateOfBirth, salary, rating);

            restTemplate.put(VETS_URL + "/{id}", vet, id);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void printAllVetsUI() {
        VetsDTO vets = restTemplate.getForObject(VETS_URL, VetsDTO.class);
        if (vets != null && vets.getVets() != null) {
            vets.getVets().forEach(System.out::println);
        } else {
            System.out.println("No results");
        }
    }

    private void printAllVetPatientsUI() {
        System.out.println("Read vet id");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());

            PetsDTO patients = restTemplate.getForObject(VETS_URL + "/patients/{id}", PetsDTO.class, id);
            if (patients != null && patients.getPets() != null) {
                patients.getPets().forEach(System.out::println);
            } else {
                System.out.println("No results");
            }
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void printAllVetAppointmentsUI() {
        System.out.println("Read vet id");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());

            AppointmentsDTO appointments = restTemplate.getForObject(VETS_URL + "/appointments/{id}", AppointmentsDTO.class, id);
            if (appointments != null && appointments.getAppointments() != null) {
                appointments.getAppointments().forEach(System.out::println);
            } else {
                System.out.println("No results");
            }
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }


    // Appointment Operations

    private void addAppointmentUI() {
        System.out.println("Read appointment {petId, vetId, type, date}");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long petId = Long.valueOf(bufferRead.readLine());
            Long vetId = Long.valueOf(bufferRead.readLine());
            String type = bufferRead.readLine();
            String date = bufferRead.readLine();
            AppointmentDTO appointment = new AppointmentDTO(petId, vetId, type, date);

            restTemplate.postForObject(APPOINTMENTS_URL, appointment, AppointmentDTO.class);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void deleteAppointmentUI() {
        System.out.println("Read appointment id");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());

            restTemplate.delete(APPOINTMENTS_URL + "/{id}", id);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void updateAppointmentUI() {
        System.out.println("Read appointment {id, petId, vetId, type, date}");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());
            Long petId = Long.valueOf(bufferRead.readLine());
            Long vetId = Long.valueOf(bufferRead.readLine());
            String type = bufferRead.readLine();
            String date = bufferRead.readLine();
            AppointmentDTO appointment = new AppointmentDTO(petId, vetId, type, date);

            restTemplate.put(APPOINTMENTS_URL + "/{id}", appointment, id);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void printAllAppointmentsUI() {
        AppointmentsDTO appointments = restTemplate.getForObject(APPOINTMENTS_URL, AppointmentsDTO.class);
        if (appointments != null && appointments.getAppointments() != null) {
            appointments.getAppointments().forEach(System.out::println);
        } else {
            System.out.println("No results");
        }
    }
}
