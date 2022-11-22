package Repository;

import Model.IVehicle;

import java.util.Objects;

public class Repo implements IRepo{
    private IVehicle[] vehicles;
    private int size, capacity;

    public Repo(){
        this.vehicles = new IVehicle[100];
        this.size = 0;
        this.capacity = this.vehicles.length;
    }

    @Override
    public IVehicle[] getAll() {
        return this.vehicles;
    }

    @Override
    public int getSize(){
        return this.size;
    }

    @Override
    public void add(IVehicle v) throws Exception {
        if (this.size >= capacity){
            throw new Exception("Repository is full!");
        }

        boolean found = false;
        int index = 0;
        for (IVehicle veh : this.vehicles){
            if (veh == null){
                break;
            }
            if (veh.getRepairCost() == v.getRepairCost() && veh.getClass() == v.getClass()) {
                found = true;
                break;
            }
        }
        if (found){
            throw new Exception("Vehicle already exists!");
        }

        this.vehicles[this.size] = v;
        this.size += 1;
    }

    @Override
    public void delete(IVehicle v) throws Exception {
        boolean found = false;
        int index = 0;
        for (IVehicle veh : this.vehicles){
            if (veh == null){
                break;
            }
            if (veh.getRepairCost() == v.getRepairCost() && veh.getClass() == v.getClass()) {
                    found = true;
                    this.vehicles[index] = this.vehicles[this.size - 1];
                    this.vehicles[this.size - 1] = null;
                    this.size -= 1;
                    break;
            }
            index += 1;
        }
        if (!found){
            throw new Exception("Vehicle does not exist!");
        }
    }

    @Override
    public IVehicle[] filter(int desiredPrice) {
        IVehicle[] filteredVehicles = new IVehicle[this.size];
        int filteredIndex = 0;

        for (IVehicle veh : this.vehicles){
            if (veh == null) {
                break;
            }
            if (veh.checkRepairCost(desiredPrice)) {
                filteredVehicles[filteredIndex] = veh;
                filteredIndex += 1;
            }
        }
        return filteredVehicles;
    }
}
