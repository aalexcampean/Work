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

/**
 * @author radu.
 */
public class PetConsole {
    private PetService petService;
    //private PetValidator petValidator;

    public PetConsole(PetService petService){ //PetValidator petValidator) {
        this.petService = petService;
        //this.petValidator = petValidator;
    }

    public void printMenu() {
        System.out.println("1.Add a pet");
        System.out.println("2.Print all pets");
        System.out.println("3.Filter pets by their name");
        System.out.println("4.Remove a pet");
        System.out.println("5.Update a pet");
        System.out.println("0.Exit");
    }

    public void runConsole(){
        printMenu();

        try{
            System.out.println("Input option: ");
            BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
            String option = bufferRead.readLine();
            while (!Objects.equals(option, "0")) {
                if (Objects.equals(option, "1"))
                    addPet();
                else if (Objects.equals(option, "2"))
                    printAllPets();
                else if (Objects.equals(option, "3"))
                    filterPets();
                else if (Objects.equals(option,"4"))
                    removePet();
                else if (Objects.equals(option,"5"))
                    updatePet();
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

    private void filterPets() {
        System.out.println("Input the string to be filtered by: ");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            String str = bufferRead.readLine();
            System.out.println("Filtered pets with name containing: " + str);
            Set<Pet> pets = petService.filterPetsByName(str);
            pets.stream().forEach(System.out::println);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    private void printAllPets() {
        Set<Pet> pets = petService.getAllPets();
        pets.stream().forEach(System.out::println);
    }

    private void addPet() {
        try {
            Pet pet = readPet();
            //petService.getRepo().getValidator().validate(pet);
            petService.addPet(pet);
            System.out.println("Pet was added!");
        } catch (ValidatorException e) {
            //e.printStackTrace();
            System.out.println(e.getMessage());
            //System.exit(1);
        }

    }

    private void removePet() {
        System.out.println("Enter the ID of the pet to be removed: ");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
        //Long id = Long.valueOf(bufferRead.readLine());
        String str = String.valueOf(bufferRead.readLine());
        boolean allDigits = true;
        for (int i = 0; i < str.length(); i++) {

            if (!Character.isDigit(str.charAt(i))) {
               allDigits = false;
               break;
            }
        }
        if(!allDigits)
            System.out.println("IDs can only be positive integers!");
        else {
            long id = Long.parseLong(str);
            petService.removePet(id);
            System.out.println("Pet was successfully removed!");

        }
        } catch (IOException ex) {
            //ex.printStackTrace();
            System.out.println("IDs can only be positive integers!");
            //System.exit(1);
        }
    }
    private void updatePet() throws IOException {
        System.out.println("Enter the ID of the pet to be updated: ");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));

        //Long id = Long.valueOf(bufferRead.readLine());
        String str = String.valueOf(bufferRead.readLine());
        boolean allDigits = true;
        for (int i = 0; i < str.length(); i++) {

            if (!Character.isDigit(str.charAt(i))) {
                allDigits = false;
                break;
            }
        }
        if(!allDigits)
            System.out.println("IDs can only be positive integers!");
        else
        {

            try {
                System.out.println("Enter the new species, breed, name, person ID:");
                long id = Long.parseLong(str);
                String species = bufferRead.readLine();
                String breed = bufferRead.readLine();
                String petName = bufferRead.readLine();
                int personId = Integer.parseInt(bufferRead.readLine());// ...

                Pet pet = new Pet(species,breed,petName,personId);
                pet.setId(id);
                petService.updatePet(pet);
                System.out.println("Pet was updated (if the id does not exist, nothing was done)");

            } catch (IOException|ValidatorException ex) {
                //ex.printStackTrace();
                System.out.println(ex.getMessage());
                //System.exit(1);
            }

        }

        }

    private Pet readPet() {
        System.out.println("Read Pet {id, species, breed, petName, personId}");

        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());// ...
            String species = bufferRead.readLine();
            String breed = bufferRead.readLine();
            String petName = bufferRead.readLine();
            int personId = Integer.parseInt(bufferRead.readLine());// ...

            Pet pet = new Pet(species,breed,petName,personId);
            pet.setId(id);

            return pet;
        } catch (IOException|ValidatorException ex) {
            //ex.printStackTrace();
            System.out.println(ex.getMessage());
            //System.exit(1);
        }
        return null;
    }
}
