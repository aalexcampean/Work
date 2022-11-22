package Controller;

import Model.Car;
import Model.IVehicle;
import Model.Motorcycle;
import Model.Truck;
import Repository.Repo;

import java.util.Objects;

public class Controller {
    private Repo repo;

    public Controller(Repo givenRepo){
        this.repo = givenRepo;
    }

    public Repo getRepo(){
        return this.repo;
    }

    public IVehicle[] getEntities(){
        return this.repo.getAll();
    }

    public int getNrOfEntities(){
        return this.repo.getSize();
    }

    public void add(String type, int repairPrice) throws Exception{
        if (repairPrice <= 0){
            throw new Exception("Repair price cannot be < 0!");
        }
        IVehicle vehicle = null;

        if (Objects.equals(type, "car")) {
            vehicle = new Car(repairPrice);
        }
        else if (Objects.equals(type, "truck")) {
            vehicle = new Truck(repairPrice);
        }
        else if (Objects.equals(type, "motorcycle")) {
            vehicle = new Motorcycle(repairPrice);
        }

        this.repo.add(vehicle);
    }

    public void delete(String type, int repairPrice) throws Exception{
        IVehicle vehicle = null;

        if (Objects.equals(type, "car")) {
            vehicle = new Car(repairPrice);
        }
        else if (Objects.equals(type, "truck")) {
            vehicle = new Truck(repairPrice);
        }
        else if (Objects.equals(type, "motorcycle")) {
            vehicle = new Motorcycle(repairPrice);
        }

        this.repo.delete(vehicle);
    }

    public IVehicle[] filter(int desiredPrice){
        return this.repo.filter(desiredPrice);
    }
}
