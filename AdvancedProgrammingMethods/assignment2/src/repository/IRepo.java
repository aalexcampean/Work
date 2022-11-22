package repository;

import model.PrgState;

public interface IRepo {
    PrgState getCurrentPrg();
    PrgState getPrgAtPos(int pos);
    void addPrg(PrgState newPrg);
}
