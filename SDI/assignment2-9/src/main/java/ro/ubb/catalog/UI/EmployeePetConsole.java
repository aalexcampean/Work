package ro.ubb.catalog.UI;

import ro.ubb.catalog.Domain.EmployeePet;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Service.EmployeePetService;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Objects;
import java.util.Set;

public class EmployeePetConsole {
    private EmployeePetService employeePetService;

    public EmployeePetConsole(EmployeePetService employeePetService) {
        this.employeePetService = employeePetService;
    }

    public void printMenu() {
        System.out.println("1. Add an employee-pet");
        System.out.println("2. Print all employee-pets");
        System.out.println("3. Filter employee-pet by their type of action");
        System.out.println("4. Delete an employee-pet");
        System.out.println("5. Update an employee-pet");
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
                    addEmployeePet();
                else if (Objects.equals(option, "2"))
                    printAllEmployeePets();
                else if (Objects.equals(option, "3"))
                    filterEmployeePets();
                else if (Objects.equals(option,"4"))
                    deleteEmployeePets();
                else if (Objects.equals(option,"5"))
                    updateEmployeePets();
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
    private EmployeePet readEmployeePet() {
        System.out.println("Read EmployeePet {id, employeeId, petId, typeOfAction, date}");

        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            System.out.println("Enter ID: ");
            Long id = Long.valueOf(bufferRead.readLine());
            System.out.println("Enter employeeId: ");
            int employeeId = Integer.parseInt(bufferRead.readLine());
            System.out.println("Enter petId: ");
            int petId = Integer.parseInt(bufferRead.readLine());
            System.out.println("Enter typeOfAction: ");
            String typeOfAction = bufferRead.readLine();
            System.out.println("Enter date (DD-MM-YYYY): ");
            String date = bufferRead.readLine();

            EmployeePet employeePet = new EmployeePet(employeeId, petId, typeOfAction, date);
            employeePet.setId(id);
            System.out.println("x");
            return employeePet;
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return null;
    }

    // add
    private void addEmployeePet() {
        try {
            EmployeePet employeePet = readEmployeePet();
            employeePetService.addEmployeePet(employeePet);
            System.out.println("EmployeePet was added!");
        } catch (ValidatorException e) {
            //e.printStackTrace();
            System.out.println(e.getMessage());
            System.exit(1);
        }
    }

    // print all
    private void printAllEmployeePets() {
        Set<EmployeePet> employeePets = employeePetService.getAllEmployeePets();
        employeePets.forEach(System.out::println);
    }

    // filter
    private void filterEmployeePets() {
        System.out.println("Input the type of action (string) to be filtered by: ");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            String str = bufferRead.readLine();
            System.out.println("Filtered employee-pets with the type of action: " + str);
            Set<EmployeePet> employeePets = employeePetService.filterEmployeePetsByType(str);
            employeePets.forEach(System.out::println);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // delete
    private void deleteEmployeePets() {
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
                employeePetService.deleteEmployeePet(id);
                System.out.println("Surgery with id: " + stringId  + " was successfully deleted!");
            }
        } catch (IOException ex) {
            //ex.printStackTrace();
            System.out.println("IDs can only be positive integers!");
            //System.exit(1);
        }
    }

    // update
    private void updateEmployeePets() throws IOException {
        System.out.println("Enter the ID of the employee-pet to be updated: ");
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
        else {
            try {
                System.out.println("Enter the new data about the employee-pet:");
                long id = Long.parseLong(stringId);
                System.out.println("Enter employeeId: ");
                int employeeId = Integer.parseInt(bufferRead.readLine());
                System.out.println("Enter petId: ");
                int petId = Integer.parseInt(bufferRead.readLine());
                System.out.println("Enter typeOfAction: ");
                String typeOfAction = bufferRead.readLine();
                System.out.println("Enter date (DD-MM-YYYY): ");
                String date = bufferRead.readLine();
                EmployeePet employeePet = new EmployeePet(employeeId, petId, typeOfAction, date);
                employeePet.setId(id);
                employeePetService.updateEmployeePet(employeePet);
                System.out.println("EmployeePet with id " + stringId + " was updated (if the id does not exist, nothing was done)");

            } catch (IOException ex) {
                //ex.printStackTrace();
                System.out.println(ex.getMessage());
                //System.exit(1);
            }
        }
    }
}
