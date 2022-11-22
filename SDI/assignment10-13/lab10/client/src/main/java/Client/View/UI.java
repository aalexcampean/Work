package Client.View;

import Client.Controller.AppointmentController;
import Client.Controller.OwnerController;
import Client.Controller.PetController;
import Client.Controller.VetController;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

public class UI {
    private OwnerController ownerController;
    private PetController petController;
    private VetController vetController;
    private AppointmentController appointmentController;

    public UI(OwnerController ownerController, PetController petController, VetController vetController, AppointmentController appointmentController) {
        this.ownerController = ownerController;
        this.petController = petController;
        this.vetController = vetController;
        this.appointmentController = appointmentController;
    }

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

            ownerController.addOwner(firstName, lastName, email, phoneNumber, dateOfBirth).whenComplete((status, exception) -> {
                if (exception == null)
                    System.out.println(status);
                else System.out.println(exception.getMessage());
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void deleteOwnerUI() {
        System.out.println("Read owner id");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());

            ownerController.deleteOwner(id).whenComplete((status, exception) -> {
                if (exception == null)
                    System.out.println(status);
                else System.out.println(exception.getMessage());
            });
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

            ownerController.updateOwner(id, firstName, lastName, email, phoneNumber, dateOfBirth).whenComplete((status, exception) -> {
                if (exception == null)
                    System.out.println(status);
                else System.out.println(exception.getMessage());
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void printAllOwnersUI() {
        ownerController.getOwners().whenComplete((status, exception) -> {
            if (exception == null)
                status.forEach(owner -> System.out.println(owner.toString()));
            else System.out.println(exception.getMessage());
        });
    }

    private void printAllOwnerPets() {
        System.out.println("Read owner id");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());

            ownerController.getOwnerPets(id).whenComplete((status, exception) -> {
                if (exception == null)
                    status.forEach(pet -> System.out.println(pet.toString()));
                else System.out.println(exception.getMessage());
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }


    // Pet Operations

    private void addPetUI() {
        System.out.println("Read pet {species, breed, name, dateOfEnrolment, personId}");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            String species = bufferRead.readLine();
            String breed = bufferRead.readLine();
            String name = bufferRead.readLine();
            String dateOfEnrolment = bufferRead.readLine();
            Long personId = Long.valueOf(bufferRead.readLine());

            petController.addPet(species, breed, name, dateOfEnrolment, personId).whenComplete((status, exception) -> {
                if (exception == null)
                    System.out.println(status);
                else System.out.println(exception.getMessage());
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void deletePetUI() {
        System.out.println("Read pet id");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());

            petController.deletePet(id).whenComplete((status, exception) -> {
                if (exception == null)
                    System.out.println(status);
                else System.out.println(exception.getMessage());
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void updatePetUI() {
        System.out.println("Read pet {id, species, breed, name, dateOfEnrolment, personId}");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());
            String species = bufferRead.readLine();
            String breed = bufferRead.readLine();
            String name = bufferRead.readLine();
            String dateOfEnrolment = bufferRead.readLine();
            Long personId = Long.valueOf(bufferRead.readLine());

            petController.updatePet(id, species, breed, name, dateOfEnrolment, personId).whenComplete((status, exception) -> {
                if (exception == null)
                    System.out.println(status);
                else System.out.println(exception.getMessage());
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void printAllPetsUI() {
        petController.getPets().whenComplete((status, exception) -> {
            if (exception == null)
                status.forEach(pet -> System.out.println(pet.toString()));
            else System.out.println(exception.getMessage());
        });
    }

    private void printPetOwnerUI() {
        System.out.println("Read pet id");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());

            petController.getPetOwner(id).whenComplete((status, exception) -> {
                if (exception == null)
                    System.out.println(status);
                else System.out.println(exception.getMessage());
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void printPetAppointmentsUI() {
        System.out.println("Read pet id");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());

            petController.getPetAppointments(id).whenComplete((status, exception) -> {
                if (exception == null)
                    status.forEach(appointment -> System.out.println(appointment.toString()));
                else System.out.println(exception.getMessage());
            });
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

            vetController.addVet(firstName, lastName, email, phoneNumber, dateOfBirth, salary, rating).whenComplete((status, exception) -> {
                if (exception == null)
                    System.out.println(status);
                else System.out.println(exception.getMessage());
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void deleteVetUI() {
        System.out.println("Read vet id");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());

            vetController.deleteVet(id).whenComplete((status, exception) -> {
                if (exception == null)
                    System.out.println(status);
                else System.out.println(exception.getMessage());
            });
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

            vetController.updateVet(id, firstName, lastName, email, phoneNumber, dateOfBirth, salary, rating).whenComplete((status, exception) -> {
                if (exception == null)
                    System.out.println(status);
                else System.out.println(exception.getMessage());
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void printAllVetsUI() {
        vetController.getVets().whenComplete((status, exception) -> {
            if (exception == null)
                status.forEach(vet -> System.out.println(vet.toString()));
            else System.out.println(exception.getMessage());
        });
    }

    private void printAllVetPatientsUI() {
        System.out.println("Read vet id");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());

            vetController.getVetPatients(id).whenComplete((status, exception) -> {
                if (exception == null)
                    status.forEach(pet -> System.out.println(pet.toString()));
                else System.out.println(exception.getMessage());
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void printAllVetAppointmentsUI() {
        System.out.println("Read vet id");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());

            vetController.getVetAppointments(id).whenComplete((status, exception) -> {
                if (exception == null)
                    status.forEach(appointment -> System.out.println(appointment.toString()));
                else System.out.println(exception.getMessage());
            });
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

            appointmentController.addAppointment(petId, vetId, type, date).whenComplete((status, exception) -> {
                if (exception == null)
                    System.out.println(status);
                else System.out.println(exception.getMessage());
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void deleteAppointmentUI() {
        System.out.println("Read appointment id");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());

            appointmentController.deleteAppointment(id).whenComplete((status, exception) -> {
                if (exception == null)
                    System.out.println(status);
                else System.out.println(exception.getMessage());
            });
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

            appointmentController.updateAppointment(id, petId, vetId, type, date).whenComplete((status, exception) -> {
                if (exception == null)
                    System.out.println(status);
                else System.out.println(exception.getMessage());
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void printAllAppointmentsUI() {
        appointmentController.getAppointments().whenComplete((status, exception) -> {
            if (exception == null)
                status.forEach(appointment -> System.out.println(appointment.toString()));
            else System.out.println(exception.getMessage());
        });
    }
}
