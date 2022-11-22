package repository;

import model.PrgState;
import model.adtContainers.MyList;

public class Repo implements IRepo{
    private MyList<PrgState> myPrgStateList;

    public Repo() {
        this.myPrgStateList = new MyList<PrgState>();
    }

    @Override
    public PrgState getCurrentPrg() {
        return this.myPrgStateList.get(0);
    }

    @Override
    public PrgState getPrgAtPos(int pos) {
        return this.myPrgStateList.get(pos);
    }

    @Override
    public void addPrg(PrgState newPrg) {
        this.myPrgStateList.add(newPrg);
    }


}
