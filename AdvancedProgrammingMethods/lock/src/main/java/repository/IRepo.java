package repository;

import model.PrgState;
import model.adtContainers.IList;

import java.util.List;

public interface IRepo {
    void addPrg(PrgState newPrg);
    IList<PrgState> getPrgList();
    void setPrgList(IList<PrgState> newPrgList);
    void logPrgStateExec(PrgState providedPrgState) throws Exception;
}
