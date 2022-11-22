package ro.ubb.catalog.UI;

import ro.ubb.catalog.Domain.Surgery;
import ro.ubb.catalog.Domain.Validators.SurgeryValidator;
import ro.ubb.catalog.Service.SurgeryService;
import ro.ubb.catalog.Domain.Validators.ValidatorException;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Objects;
import java.util.Set;

public class SurgeryConsole {
    private SurgeryService surgeryService;

    public SurgeryConsole(SurgeryService surgeryService) {
        this.surgeryService = surgeryService;
    }

    public void printMenu() {
        System.out.println("1. Add a surgery");
        System.out.println("2. Print all surgeries");
        System.out.println("3. Filter surgeries by their surgery type");
        System.out.println("4. Delete a surgery");
        System.out.println("5. Update a surgery");
        System.out.println("0. Exit");
    }

    public void runConsole() {
        printMenu();
        try{
            System.out.println("Input option: ");
            BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
            String option = bufferRead.readLine();
            while (!Objects.equals(option, "0")) {
                if (Objects.equals(option, "1"))
                    addSurgery();
                else if (Objects.equals(option, "2"))
                    printAllSurgeries();
                else if (Objects.equals(option, "3"))
                    filterSurgeries();
                else if (Objects.equals(option,"4"))
                    deleteSurgery();
                else if (Objects.equals(option,"5"))
                    updateSurgery();
                else System.out.println("Invalid option!");

                printMenu();
                System.out.println("Input option: ");
                option = bufferRead.readLine();
            }
        }
        catch(IOException ex) {
            ex.printStackTrace();
        }
    }

    // read
    private Surgery readSurgery() {
        System.out.println("Read Surgery {id, petId, vetId, surgeryDate, surgeryType}");

        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            System.out.println("Enter ID: ");
            Long id = Long.valueOf(bufferRead.readLine());
            System.out.println("Enter petId: ");
            int petId = Integer.parseInt(bufferRead.readLine());
            System.out.println("Enter vetId: ");
            int vetId = Integer.parseInt(bufferRead.readLine());
            System.out.println("Enter surgeryDate (DD-MM-YYYY): ");
            String surgeryDate = bufferRead.readLine();
            System.out.println("Enter surgeryType: ");
            String surgeryType = bufferRead.readLine();
            Surgery surgery = new Surgery(petId, vetId, surgeryDate, surgeryType);
            surgery.setId(id);
            System.out.println("x");
            return surgery;
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return null;
    }

    // add
    private void addSurgery() {
        try {
            Surgery surgery = readSurgery();
            surgeryService.addSurgery(surgery);
            System.out.println("Surgery was added!");
        } catch (ValidatorException e) {
            //e.printStackTrace();
            System.out.println(e.getMessage());
            System.exit(1);
        }
    }

    // print all
    private void printAllSurgeries() {
        Set<Surgery> surgeries = surgeryService.getAllSurgeries();
        surgeries.forEach(System.out::println);
    }

    // filter
    private void filterSurgeries() {
        System.out.println("Input the surgery type (string) to be filtered by: ");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            String str = bufferRead.readLine();
            System.out.println("Filtered surgeries with the surgery type: " + str);
            Set<Surgery> surgeries = surgeryService.filterSurgeriesByType(str);
            surgeries.forEach(System.out::println);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // delete
    private void deleteSurgery() {
        System.out.println("Enter the ID of the surgery to be deleted: ");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            // Long id = Long.valueOf(bufferRead.readLine());
            String stringId = String.valueOf(bufferRead.readLine());
            boolean allDigits = true;
            for (int i = 0; i < stringId.length(); i++) {
                if (!Character.isDigit(stringId.charAt(i))) {
                    allDigits = false;
                    break;
                }
            }
            if(!allDigits)
                System.out.println("IDs can only be positive integers!");
            else {
                long id = Long.parseLong(stringId);
                surgeryService.deleteSurgery(id);
                System.out.println("Surgery with id: " + stringId  + " was successfully deleted!");

            }
        } catch (IOException ex) {
            //ex.printStackTrace();
            System.out.println("IDs can only be positive integers!");
            //System.exit(1);
        }
    }

    // update
    private void updateSurgery() throws IOException {
        System.out.println("Enter the ID of the surgery to be updated: ");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));

        // Long id = Long.valueOf(bufferRead.readLine());
        String stringId = String.valueOf(bufferRead.readLine());
        boolean allDigits = true;
        for (int i = 0; i < stringId.length(); i++) {
            if (!Character.isDigit(stringId.charAt(i))) {
                allDigits = false;
                break;
            }
        }
        if(!allDigits)
            System.out.println("IDs can only be positive integers!");
        else
        {
            try {
                System.out.println("Enter the new data about the surgery:");
                long id = Long.parseLong(stringId);
                System.out.println("Enter petId: ");
                int petId = Integer.parseInt(bufferRead.readLine());
                System.out.println("Enter vetId: ");
                int vetId = Integer.parseInt(bufferRead.readLine());
                System.out.println("Enter surgeryDate (DD-MM-YYYY): ");
                String surgeryDate = bufferRead.readLine();
                System.out.println("Enter surgeryType: ");
                String surgeryType = bufferRead.readLine();

                Surgery surgery = new Surgery(petId, vetId, surgeryDate, surgeryType);
                surgery.setId(id);
                surgeryService.updateSurgery(surgery);
                System.out.println("Surgery with id " + stringId + " was updated (if the id does not exist, nothing was done)");

            } catch (IOException ex) {
                //ex.printStackTrace();
                System.out.println(ex.getMessage());
                //System.exit(1);
            }
        }
    }
}
