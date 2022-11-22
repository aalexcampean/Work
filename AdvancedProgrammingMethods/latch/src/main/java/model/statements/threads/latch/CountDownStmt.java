package model.statements.threads.latch;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.ILatch;
import model.statements.IStmt;
import model.types.IType;
import model.types.IntType;
import model.values.IValue;
import model.values.IntValue;

import java.io.IOException;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class CountDownStmt implements IStmt {
    private String var;
    private static Lock lock = new ReentrantLock();

    public CountDownStmt(String v) {
        this.var = v;
    }

    @Override
    public PrgState execute(PrgState state) throws IOException {
        IDictionary<String, IValue> symTbl = state.getSymTable();
        ILatch latchTbl = state.getLatchTbl();

        if (symTbl.containsKey(this.var)){
            IntValue foundIndex = (IntValue)(symTbl.get(this.var));
            if (latchTbl.containsKey(foundIndex.getValue())) {
                lock.lock();
                // retrieving the data from the latch table
                Integer latchValue = latchTbl.get(foundIndex.getValue());

                if (latchValue > 0) {
                    latchTbl.update(foundIndex.getValue(), latchValue - 1);
                    state.getOut().add(new IntValue(state.getId()));
                }

                lock.unlock();
            }
        } else throw new CustomException("Variable is undefined!");

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
        return "countDown(" + this.var + ")";
    }
}
