package Model;

public interface IVehicle {
    public int getRepairCost();
    public void setRepairCost(int givenCost);
    public boolean checkRepairCost(int givenCost);
    public String toString();
}
