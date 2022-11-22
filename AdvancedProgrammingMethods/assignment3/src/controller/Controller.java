package controller;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IStack;
import model.statements.IStmt;
import repository.IRepo;

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
                System.out.println(prg.toString());
            }
            System.out.println("------- end of program\n");
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
