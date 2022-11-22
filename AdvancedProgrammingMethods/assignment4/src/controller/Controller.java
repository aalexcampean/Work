package controller;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IStack;
import model.statements.IStmt;
import model.types.RefType;
import model.values.IValue;
import model.values.RefValue;
import repository.IRepo;

import java.util.Collection;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

public class Controller {
    private IRepo repo;

    public Controller(IRepo r){
        this.repo = r;
    }

//    public void addProgram(PrgState newPrg){
//        this.repo.addPrg(newPrg);
//    }

    public PrgState oneStep(PrgState state) {
        IStack<IStmt> stk = state.getExeStack();
        if (!stk.isEmpty()){
            IStmt currentStmt = stk.pop();
            return currentStmt.execute(state);
        }
        else {
            throw new CustomException("Program state is empty!");
        }
    }

    public void allSteps(){
        PrgState prg = this.repo.getCurrentPrg();
        System.out.println(prg.toString());

        try {
            this.repo.logPrgStateExec(); // saving into the file the initial state of the repo
            while (!prg.getExeStack().isEmpty()){
                oneStep(prg);
                this.repo.logPrgStateExec();
                prg.getHeap().setContent(garbageCollector(getSymbolTableAddresses(prg.getSymTable().values()), prg.getHeap().getContent()));
                this.repo.logPrgStateExec();
                System.out.println(prg.toString());
            }
            System.out.println("------- end of program\n");
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public Set<Integer> getSymbolTableAddresses(Collection<IValue> symbolTableAddresses) {
        Set<Integer> usedSymbolTableAddresses = symbolTableAddresses.stream()
                .filter(v -> v instanceof RefValue)
                .map(v-> ((RefValue) v).getAddress())
                .collect(Collectors.toSet());

        return usedSymbolTableAddresses;
    }

    public Map<Integer, IValue> garbageCollector(Set<Integer> symbolTableAddresses, Map<Integer, IValue> heap) {

        Map<Integer, IValue> intersectedMap = heap.entrySet()
                .stream()
                .filter(v -> (symbolTableAddresses.contains(v.getKey())))
                .collect(Collectors.toMap(v -> v.getKey(), v -> v.getValue()));

        return intersectedMap;
    }
}
