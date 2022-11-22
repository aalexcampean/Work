package Model;

public class Motorcycle implements IVehicle {
    private int repairCost;

    public Motorcycle(){
    }

    public Motorcycle(int givenRepairCost){
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
        return "--Motorcycle--" + "repair cost:" + this.repairCost + "\n";
    }
}
