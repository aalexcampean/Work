package model.statements.threads.lock;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.ILock;
import model.statements.IStmt;
import model.types.IType;
import model.types.IntType;
import model.values.IValue;
import model.values.IntValue;

import java.io.IOException;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class NewLockStmt implements IStmt {
    private String var;
    private static Lock lock = new ReentrantLock();

    public NewLockStmt(String v) {
        this.var = v;
    }

    @Override
    public PrgState execute(PrgState state) throws IOException {
        IDictionary<String, IValue> symTbl = state.getSymTable();
        ILock lockTbl = state.getLockTbl();

        if (symTbl.containsKey(this.var)) {
            lock.lock();

            IntValue location = new IntValue(state.getLockTbl().getFreeAddress());
            lockTbl.add(-1);
            symTbl.update(this.var, location);

            lock.unlock();
        } else throw new CustomException("Undefined variable!");

        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        if (!typeEnv.containsKey(this.var))
            throw new CustomException("Variable is not defined!");

        if (!typeEnv.get(this.var).equals(new IntType()))
            throw new CustomException("Variable not of IntType!");

        return typeEnv;
    }

    @Override
    public String toString() {
        return "newLock(" + this.var + ")";
    }
}
