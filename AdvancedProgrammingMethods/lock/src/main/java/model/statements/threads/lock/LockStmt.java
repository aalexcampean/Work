package model.statements.threads.lock;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.ILock;
import model.adtContainers.IStack;
import model.statements.IStmt;
import model.types.IType;
import model.types.IntType;
import model.values.IValue;
import model.values.IntValue;

import java.io.IOException;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class LockStmt implements IStmt {
    private String var;
    private static Lock lock = new ReentrantLock();

    public LockStmt(String v) {
        this.var = v;
    }

    @Override
    public PrgState execute(PrgState state) throws IOException {
        IStack<IStmt> stk = state.getExeStack();
        IDictionary<String, IValue> symTbl = state.getSymTable();
        ILock lockTbl = state.getLockTbl();

        if (symTbl.containsKey(this.var)){
            if (symTbl.get(this.var).getType().equals(new IntType())) {
                IntValue foundIndex = (IntValue) (symTbl.get(this.var));
                if (lockTbl.containsKey(foundIndex.getValue())) {
                    lock.lock();
                    // retrieving the data from the lock table
                    Integer lockValue = lockTbl.get(foundIndex.getValue());

                    if (lockValue == -1) {
                        lockTbl.update(foundIndex.getValue(), state.getId());
                    } else stk.push(this);

                    lock.unlock();
                } else throw new CustomException("The index is not in the LockTable!");
            } else throw new CustomException("Variable is not of IntType!");
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
        return "lock(" + this.var + ")";
    }
}
