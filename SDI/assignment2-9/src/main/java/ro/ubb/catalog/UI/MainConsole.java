package ro.ubb.catalog.UI;

import ro.ubb.catalog.Domain.Pet;
import ro.ubb.catalog.Domain.Validators.PetValidator;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Service.PetService;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Objects;
import java.util.Set;

public class MainConsole {
    private ClinicConsole clinicConsole;
    private EmployeeConsole employeeConsole;
    private EmployeeContractConsole employeeContractConsole;
    private OwnerConsole ownerConsole;
    private PetConsole petConsole;
    private SurgeryConsole surgeryConsole;
    private VetConsole vetConsole;
    private VetContractConsole vetContractConsole;

    public MainConsole(ClinicConsole clinicConsole,
                       EmployeeConsole employeeConsole,
                       EmployeeContractConsole employeeContractConsole,
                       OwnerConsole ownerConsole,
                       PetConsole petConsole,
                       SurgeryConsole surgeryConsole,
                       VetConsole vetConsole,
                       VetContractConsole vetContractConsole) {
        this.clinicConsole = clinicConsole;
        this.employeeConsole = employeeConsole;
        this.employeeContractConsole = employeeContractConsole;
        this.ownerConsole = ownerConsole;
        this.petConsole = petConsole;
        this.surgeryConsole = surgeryConsole;
        this.vetConsole = vetConsole;
        this.vetContractConsole = vetContractConsole;
    }

    public void printMenu() {
        System.out.println("1.Manage clinics");
        System.out.println("2.Manage employees");
        System.out.println("3.Manage employees' contacts");
        System.out.println("4.Manage owners");
        System.out.println("5.Manage pets");
        System.out.println("6.Manage surgeries");
        System.out.println("7.Manage vets");
        System.out.println("8.Manage vets' contracts");
        System.out.println("0.Exit");
    }

    public void runConsole() {
        this.printMenu();
        try {
            System.out.println("Input option: ");
            BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
            String option = bufferRead.readLine();
            while (!Objects.equals(option, "0")) {
                if (Objects.equals(option, "1"))
                    this.clinicConsole.runConsole();
                else if (Objects.equals(option, "2"))
                    this.employeeConsole.runConsole();
                else if (Objects.equals(option, "3"))
                    this.employeeContractConsole.runConsole();
                else if (Objects.equals(option, "4"))
                    this.ownerConsole.runConsole();
                else if (Objects.equals(option, "5"))
                    this.petConsole.runConsole();
                else if (Objects.equals(option, "6"))
                    this.surgeryConsole.runConsole();
                else if (Objects.equals(option, "7"))
                    this.vetConsole.runConsole();
                else if (Objects.equals(option, "8"))
                    this.vetContractConsole.runConsole();

                else System.out.println("Invalid option!");

                printMenu();
                System.out.println("Input option: ");
                option = bufferRead.readLine();
            }
        } catch (IOException ex) {
            ex.printStackTrace();
        }

    }
}