package model.statements;

import model.PrgState;
import model.adtContainers.IStack;

public class CompStmt implements IStmt{
    private IStmt first;
    private IStmt second;

    public CompStmt(IStmt f, IStmt s){
        this.first = f;
        this.second = s;
    }

    public IStmt getFirst(){
        return this.first;
    }

    public IStmt getSecond(){
        return this.second;
    }

    @Override
    public PrgState execute(PrgState state) {
        IStack<IStmt> stk = state.getExeStack();
        stk.push(this.second);
        stk.push(this.first);
        return null;
    }

    @Override
    public String toString(){
        return "(" + this.first.toString() + ";" +this.second.toString() + ")";
    }
}