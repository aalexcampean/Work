package model.statements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.IStack;
import model.types.IType;

import java.io.IOException;

public class SleepStmt implements IStmt{
    public Integer value;

    public SleepStmt(Integer v) {
        this.value = v;
    }

    @Override
    public PrgState execute(PrgState state) throws IOException {
        IStack<IStmt> stk = state.getExeStack();
        if (this.value != 0) {
            IStmt newStmt = new SleepStmt(this.value - 1);
            stk.push(newStmt);
        }
        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "sleep(" + this.value.toString() + ")";
    }
}
