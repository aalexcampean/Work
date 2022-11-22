package Model;

public class Car implements IVehicle {
    private int repairCost;

    public Car(){
    }

    public Car(int givenRepairCost){
        this.repairCost = givenRepairCost;
    }

    @Override
    public int getRepairCost(){
        return this.repairCost;
    }

    @Override
    public void setRepairCost(int givenCost){
        this.repairCost = givenCost;
    }

    @Override
    public boolean checkRepairCost(int givenCost){
        return this.repairCost > givenCost;
    }

    @Override
    public String toString(){
        return "--Car--" + "repair cost:" + this.repairCost + "\n";
    }
}
