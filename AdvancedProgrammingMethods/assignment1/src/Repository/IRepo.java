package Repository;

import Model.IVehicle;

public interface IRepo {
    public IVehicle[] getAll();
    public int getSize();
    public void add(IVehicle v) throws Exception;
    public void delete(IVehicle v) throws Exception;
    public IVehicle[] filter(int desiredPrice);
}
