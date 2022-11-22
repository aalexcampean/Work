package repository;

import model.PrgState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.Path;
import java.nio.file.Paths;

public class Repo implements IRepo{
    private PrgState prgState;
    private Path logFilePath;
    private PrintWriter logFile;

    public Repo(PrgState pState, String fileName) {
        this.prgState = pState;
        this.logFilePath = Paths.get(fileName).toAbsolutePath();
    }

    @Override
    public PrgState getCurrentPrg() {
        return this.prgState;
    }

//    @Override
//    public PrgState getPrgAtPos(int pos) {
//        return this.prgState;
//    }
//
//    @Override
//    public void addPrg(PrgState newPrg) {
//        this.prgState.add(newPrg);
//    }

    @Override
    public void logPrgStateExec() {
        try {
            this.logFile = new PrintWriter(new BufferedWriter(new FileWriter(this.logFilePath.toString(), true)));
            this.logFile.println(this.getCurrentPrg().toString());
            this.logFile.close();
        }
        catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }


}
