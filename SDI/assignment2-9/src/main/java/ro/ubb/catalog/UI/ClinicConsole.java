package ro.ubb.catalog.UI;

import ro.ubb.catalog.Domain.Clinic;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Service.ClinicService;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Objects;
import java.util.Optional;
import java.util.Set;

public class ClinicConsole {
    private ClinicService clinicService;

    public ClinicConsole(ClinicService clinicService) {
        this.clinicService = clinicService;
    }

    public void printMenu() {
        System.out.println("1.Add a clinic");
        System.out.println("2.Delete a vet");
        System.out.println("3.Update a vet");
        System.out.println("4.Print all clinic");
        System.out.println("5.Filter clinics by the year they were founded in");
        System.out.println("0.Exit");
    }

    public void runConsole() {
        printMenu();
        try {
            System.out.println("Input option: ");
            BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
            String option = bufferRead.readLine();
            while (!Objects.equals(option, "0")) {
                if (Objects.equals(option, "1"))
                    addClinic();
                else if (Objects.equals(option, "2"))
                    deleteClinic();
                else if (Objects.equals(option, "3"))
                    updateClinic();
                else if (Objects.equals(option, "4"))
                    printAllClinics();
                else if (Objects.equals(option, "5"))
                    filterClinics();
                else System.out.println("Invalid option!");

                printMenu();
                System.out.println("Input option: ");
                option = bufferRead.readLine();
            }
        } catch (IOException ex) {
            ex.printStackTrace();
        }

    }

    private void addClinic() {
        try {
            Clinic inputClinic = readClinic(false);
            this.clinicService.addClinic(inputClinic);
            System.out.println("Clinic added successfully!");
        } catch (ValidatorException e) {
            System.out.println(e.getMessage());
            System.exit(1);
        }
    }

    private void deleteClinic() throws IOException {
        System.out.println("Clinic ID: ");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        long id = Long.parseLong(bufferRead.readLine());
        clinicService.deleteClinic(id);
        System.out.println("Clinic deleted successfully!");
    }

    private void updateClinic() throws IOException {
        Clinic updatedClinic = readClinic(true);
        clinicService.updateClinic(updatedClinic);
        System.out.println("Clinic updated successfully!");
    }

    private Clinic readClinic(boolean requireId) {
        if (requireId) {
            System.out.println("Read Clinic {id, name, location, yearFounded}");
        } else {
            System.out.println("Read Clinic {name, location, yearFounded}");
        }

        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            long id = 0L;
            if (requireId) {
                id = Long.parseLong(bufferRead.readLine());
            }
            String name = bufferRead.readLine();
            String location = bufferRead.readLine();
            int yearFounded = Integer.parseInt(bufferRead.readLine());

            Clinic clinic = new Clinic(name, location, yearFounded);
            clinic.setId(id);
            return clinic;
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return null;
    }

    private void printAllClinics() {
        Set<Clinic> clinics = clinicService.getAllClinics();
        clinics.forEach(System.out::println);
    }

    private void filterClinics() {
        System.out.println("Input the string that the clinics are filtered by: ");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Integer inputYear = Integer.parseInt(bufferRead.readLine());
            Set<Clinic> clinics = clinicService.filterClinicsFoundedBeforeDate(inputYear);
            clinics.forEach(System.out::println);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
