package ro.ubb.catalog.UI;

import ro.ubb.catalog.Domain.EmployeeContract;
import ro.ubb.catalog.Domain.Validators.EmployeeContractValidator;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Domain.Validators.VetContractValidator;
import ro.ubb.catalog.Domain.Vet;
import ro.ubb.catalog.Domain.VetContract;
import ro.ubb.catalog.Service.EmployeeContractService;
import ro.ubb.catalog.Service.VetContractService;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.time.LocalDate;
import java.util.Objects;
import java.util.Optional;
import java.util.Set;

public class VetContractConsole {
    private VetContractService vetService;

    public VetContractConsole(VetContractService s) {
        this.vetService = s;
    }

    public void printMenu() {
        System.out.println("1.Add a Vet Contract");
        System.out.println("2.Print all Vet Contracts");
        System.out.println("3.Filter Vet Contracts by their date");
        System.out.println("4.Delete a Vet Contract");
        System.out.println("5.Update a Vet Contract");
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
                    addVetContract();
                else if (Objects.equals(option, "2"))
                    printAllVetContracts();
                else if (Objects.equals(option, "3"))
                    filterVetContracts();
                else if (Objects.equals(option, "4"))
                    deleteVetContract();
                else if (Objects.equals(option, "5"))
                    updateVetContract();
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

    private void updateVetContract() {
        System.out.println("Update Vet Contract");

        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            System.out.println("Enter ID: ");
            Long id = Long.valueOf(bufferRead.readLine());
            System.out.println("Enter Date (YYYY-MM-DD): ");
            LocalDate date = LocalDate.parse(bufferRead.readLine());
            System.out.println("Enter VetID: ");
            int vid = Integer.parseInt(bufferRead.readLine());
            System.out.println("Enter ClinicID: ");
            int cid = Integer.parseInt(bufferRead.readLine());// ...
            VetContract vc = new VetContract(vid, cid, date);
            vc.setId(id);
            Optional<VetContract> uvc = vetService.updateVetContract(vc);
            if(uvc.isPresent()) {
                System.out.println("! Updated !");
            }
            else {
                System.out.println("X Not updated X");
            }
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void deleteVetContract() {
        System.out.println("Enter the Vet Contract ID to be removed: ");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        long id = 0;
        try {
            id = Long.parseLong(bufferRead.readLine());
            Optional<VetContract> optional = vetService.deleteVetContract(id);
            if (optional.isPresent()) {
                System.out.println("Vet was successfully removed!");
            }
            else {
                System.out.println("X Not removed X");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void filterVetContracts() {
        System.out.println("Input the max date (format YYYY-MM-DD): ");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            String str = bufferRead.readLine();
            System.out.println("Filtered VetContracts before the date: " + str);
            Set<VetContract> vcs = this.vetService.filterVetContracts(str);
            vcs.forEach(System.out::println);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void printAllVetContracts() {
        Set<VetContract> ecs = vetService.getAllVetContracts();
        ecs.forEach(System.out::println);
    }

    private void addVetContract() {
        try {
            VetContract vc = readVetContract();
            vetService.addVetContract(vc);
            System.out.println("VetContract was added!");
        } catch (ValidatorException e) {
            //e.printStackTrace();
            System.out.println(e.getMessage());
            System.exit(1);
        }
    }

    private VetContract readVetContract() {
        System.out.println("Read Vet Contract");

        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            System.out.println("Enter ID: ");
            Long id = Long.valueOf(bufferRead.readLine());
            System.out.println("Enter Date (YYYY-MM-DD): ");
            LocalDate date = LocalDate.parse(bufferRead.readLine());
            System.out.println("Enter VetID: ");
            int vid = Integer.parseInt(bufferRead.readLine());
            System.out.println("Enter ClinicID: ");
            int cid = Integer.parseInt(bufferRead.readLine());// ...
            VetContract vc = new VetContract(vid, cid, date);
            vc.setId(id);
            System.out.println("x");
            return vc;
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return null;
    }
}
