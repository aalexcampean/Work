package ro.ubb.catalog.UI;

import ro.ubb.catalog.Domain.Vet;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Service.VetService;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Objects;
import java.util.Optional;
import java.util.Set;

public class VetConsole {
    private VetService vetService;

    public VetConsole(VetService s) {
        this.vetService = s;
    }


    public void printMenu() {
        System.out.println("1.Add a vet");
        System.out.println("2.Print all vets");
        System.out.println("3.Filter vets by rating");
        System.out.println("4.Delete a vet");
        System.out.println("5.Update a vet");
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
                    addVets();
                else if (Objects.equals(option, "2"))
                    printAllVets();
                else if (Objects.equals(option, "3"))
                    filterVets();
                else if (Objects.equals(option, "4"))
                    deleteVet();
                else if (Objects.equals(option, "5"))
                    updateVet();
                else System.out.println("Invalid option!");
                printMenu();
                System.out.println("Input option: ");
                option = bufferRead.readLine();
            }
        } catch (IOException ex) {
            ex.printStackTrace();
        } catch (ParserConfigurationException e) {
            e.printStackTrace();
        } catch (TransformerException e) {
            e.printStackTrace();
        }
    }


    private void printAllVets() {
        Set<Vet> vets = vetService.getAllVets();
        vets.forEach(System.out::println);
    }

    private void addVets() {

        Vet vet = readVet();
        try {
            vetService.addVet(vet);
        } catch (ValidatorException e) {
            e.printStackTrace();
        }
    }

    private Vet readVet() {
        System.out.println("Read vet");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());// ...
            String firstName = bufferRead.readLine();
            String lastName = bufferRead.readLine();
            int sal = Integer.parseInt(bufferRead.readLine());
            int rate = Integer.parseInt(bufferRead.readLine());// ...
            String date = bufferRead.readLine();
            Vet v = new Vet(firstName, lastName, sal, rate, date);
            v.setId(id);
            System.out.println("Vet read");
            return v;
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return null;
    }

    private void filterVets() {
        System.out.println("Input the rating to be filtered by: ");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            int rating = Integer.parseInt(bufferRead.readLine());
            System.out.println("Filtered vets with rating bigger than : " + rating);
            Set<Vet> vets = vetService.filterVetsbyRating(rating);
            vets.stream().forEach(System.out::println);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void deleteVet() throws IOException, ParserConfigurationException, TransformerException {
        System.out.println("Enter the ID of the vet to be removed: ");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        long id = Long.parseLong(bufferRead.readLine());
        Optional<Vet> optional = vetService.deleteVet(id);
        System.out.println("Vet was successfully removed!");
    }

    private void updateVet() throws IOException, ParserConfigurationException, TransformerException {
        System.out.println("Enter the ID of the vet to be updated: ");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        long id = Long.parseLong(bufferRead.readLine());
        System.out.println("Enter the new first name:");
        String fname = bufferRead.readLine();
        System.out.println("Enter the new last name:");
        String lname = bufferRead.readLine();
        System.out.println("Enter the new salary");
        int sal = Integer.parseInt(bufferRead.readLine());
        System.out.println("Enter the new rating");
        int rat = Integer.parseInt(bufferRead.readLine());
        System.out.println("Enter the new date");
        String date = bufferRead.readLine();
        Vet vet = new Vet(fname, lname, sal, rat, date);
        vet.setId(id);
        vetService.updateVet(vet);
        System.out.println("Vet was updated ");
    }
}