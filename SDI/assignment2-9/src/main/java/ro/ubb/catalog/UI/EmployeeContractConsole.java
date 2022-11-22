package ro.ubb.catalog.UI;

import ro.ubb.catalog.Domain.EmployeeContract;  
import ro.ubb.catalog.Domain.Validators.*;
import ro.ubb.catalog.Service.EmployeeContractService;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.time.LocalDate;
import java.util.Objects;
import java.util.Set;
import java.util.Optional;

public class EmployeeContractConsole {
    private EmployeeContractService ecService;
    private EmployeeContractValidator employeeContractValidator;

    public EmployeeContractConsole(EmployeeContractService s, EmployeeContractValidator ecValidator) {
        this.ecService = s;
        this.employeeContractValidator = ecValidator;
    }

    public void printMenu() {
        System.out.println("1.Add an EmployeeContract");
        System.out.println("2.Print all EmployeeContracts");
        System.out.println("3.Filter EmployeeContracts by their date");
        System.out.println("4.Update EmployeeContract");
        System.out.println("5.Delete EmployeeContract");
        System.out.println("0.Exit");
    }

    public void runConsole() {
        printMenu();

        try{
            System.out.println("Input option: ");
            BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
            String option = bufferRead.readLine();
            while (!Objects.equals(option, "0")) {
                if (Objects.equals(option, "1"))
                    addEmployeeContract();
                else if (Objects.equals(option, "2"))
                    printAllEmployeeContracts();
                else if (Objects.equals(option, "3"))
                    filterEmployeeContracts();
                else if (Objects.equals(option, "4"))
                    updateEC();
                else if (Objects.equals(option, "5"))
                    deleteEC();
                else System.out.println("Invalid option!");
    
                printMenu();
                System.out.println("Input option: ");
                option = bufferRead.readLine();
            }
        }
        catch(IOException ex) {
            ex.printStackTrace();
        }
        catch (ParserConfigurationException e) {
            e.printStackTrace();
        }
        catch (TransformerException e) {
            e.printStackTrace();
        }
    }


    private void filterEmployeeContracts() {
        System.out.println("Input the max date (format YYYY-MM-DD): ");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            String str = bufferRead.readLine();
            System.out.println("Filtered EmployeeContracts before the date: " + str);
            Set<EmployeeContract> ecs = this.ecService.filterEmployeeContracts(str);
            ecs.stream().forEach(System.out::println);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    private void printAllEmployeeContracts() {
        Set<EmployeeContract> ecs = ecService.getAllEmployeeContracts();
        ecs.forEach(System.out::println);
    }

    private void addEmployeeContract() {

        try {
            EmployeeContract ec = readEmployeeContract();
            employeeContractValidator.validate(ec);
            ecService.addEmployeeContract(ec);
            System.out.println("EmployeeContract was added!");
        } catch (ValidatorException e) {
            //e.printStackTrace();
            System.out.println(e.getMessage());
            System.exit(1);
        }
    }

    private EmployeeContract readEmployeeContract() {
        System.out.println("Read employeecontract");

        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            System.out.println("Enter ID: ");
            Long id = Long.valueOf(bufferRead.readLine());
            System.out.println("Enter Date (YYYY-MM-DD): ");
            LocalDate date = LocalDate.parse(bufferRead.readLine());
            System.out.println("Enter EmployeeID: ");
            int eid = Integer.parseInt(bufferRead.readLine());
            System.out.println("Enter ClinicID: ");
            int cid = Integer.parseInt(bufferRead.readLine());// ...
            EmployeeContract ec = new EmployeeContract(date, eid, cid);
            ec.setId(id);
            System.out.println("x");
            return ec;
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return null;
    }

    private void deleteEC() throws IOException, ParserConfigurationException, TransformerException {
        System.out.println("Enter the ID of the EmployeeContract to be removed: ");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        long id = Long.parseLong(bufferRead.readLine());
        Optional<EmployeeContract> optional = ecService.deleteEmployeeContract(id);
        System.out.println("Employee contract was successfully removed!");
    }

    private void updateEC() throws IOException, ParserConfigurationException, TransformerException {
        System.out.println("Enter the ID of the EmployeeContract to be updated: ");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        long id = Long.parseLong(bufferRead.readLine());
        System.out.println("Enter the new date:");
        String date = bufferRead.readLine();
        System.out.println("Enter the new employeeID:");
        String eid = bufferRead.readLine();
        System.out.println("Enter the new clinicID: ");
        String cid = bufferRead.readLine();
        EmployeeContract ec = new EmployeeContract(LocalDate.parse(date), Integer.parseInt(eid), Integer.parseInt(cid));
        ec.setId(id);
        ecService.updateEmployeeContract(ec);
        System.out.println("EmployeeContract was updated ");
    }
}