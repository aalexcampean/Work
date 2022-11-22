package repository;

import model.PrgState;
import model.adtContainers.IList;
import model.adtContainers.MyList;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.nio.file.Path;
import java.nio.file.Paths;

public class Repo implements IRepo{
    private IList<PrgState> prgStateList;
    private Path logFilePath;
    private PrintWriter logFile;

    public Repo(PrgState pState, String fileName) {
        this.prgStateList = new MyList<PrgState>();
        this.prgStateList.add(pState);
        this.logFilePath = Paths.get(fileName).toAbsolutePath();
    }

    @Override
    public void addPrg(PrgState newPrg) {
        this.prgStateList.add(newPrg);
    }

    @Override
    public IList<PrgState> getPrgList() {
        return this.prgStateList;
    }

    @Override
    public void setPrgList(IList<PrgState> newPrgList) {
        this.prgStateList = newPrgList;
    }

    @Override
    public void logPrgStateExec(PrgState providedPrgState) throws Exception {
        this.logFile = new PrintWriter(new BufferedWriter(new FileWriter(this.logFilePath.toString(), true)));
        this.logFile.println(providedPrgState.toString());
        this.logFile.flush();
        this.logFile.close();
    }
}
