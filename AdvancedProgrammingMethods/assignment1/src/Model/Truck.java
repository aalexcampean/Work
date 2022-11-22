package Model;

public class Truck implements IVehicle {
    private int repairCost;

    public Truck(){
    }

    public Truck(int givenRepairCost){
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
        return "--Truck--" + "repair cost:" + this.repairCost + "\n";
    }
}
