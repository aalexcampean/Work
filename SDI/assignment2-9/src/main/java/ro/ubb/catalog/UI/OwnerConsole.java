package ro.ubb.catalog.UI;

import ro.ubb.catalog.Domain.Owner;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Service.OwnerService;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Set;

public class OwnerConsole {
    private OwnerService ownerService;

    public OwnerConsole(OwnerService owner_service) {
        this.ownerService = owner_service;
    }

    public void runConsole(){
        addOwners();
        //printAllOwners();
        //filterOwners();
    }

    private void addOwners(){
        while (true){
            Owner owner=readOwner();
            if(owner==null || owner.getId()<0){
                break;
        }
            try{
                ownerService.addOwner(owner);
            }catch (ValidatorException ex){
                ex.printStackTrace();
            }
    }
    }

    public Owner readOwner(){
        System.out.println("Read owner {id,OwnerId, firstName, lastName}");

        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());// ...
            int OwnerId= Integer.parseInt(bufferRead.readLine());
            String firstName = bufferRead.readLine();
            String lastName = bufferRead.readLine();


            Owner owner = new Owner(firstName, lastName);
            owner.setId(id);

            return owner;
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return null;
    }

    void printAllOwners(){
        Set<Owner> owners=ownerService.getAllOwners();
        owners.stream().forEach(System.out::println);
    }

    private void filterOwners() {
        System.out.println("filtered owners (name containing 's2'):");
        Set<Owner> owners = ownerService.filterOwnersByLastName("s2");
        owners.stream().forEach(System.out::println);
    }
}
