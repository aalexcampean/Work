package model.statements.threads.semaphore;

import exception.CustomException;
import javafx.util.Pair;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.ISemaphore;
import model.adtContainers.IStack;
import model.statements.IStmt;
import model.types.IType;
import model.types.IntType;
import model.values.IValue;
import model.values.IntValue;

import java.io.IOException;
import java.util.ArrayList;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ReleaseSemaphoreStmt implements IStmt {
    private String var;
    private static Lock lock = new ReentrantLock();

    public ReleaseSemaphoreStmt(String v) {
        this.var = v;
    }

    @Override
    public PrgState execute(PrgState state) throws IOException {
        IDictionary<String, IValue> symTbl = state.getSymTable();
        ISemaphore semaphoreTbl = state.getSemaphoreTbl();

        if (symTbl.containsKey(this.var)){
            // retrieve the IntValue associated to the var
            IValue index = symTbl.get(this.var);
            if (index.getType().equals(new IntType())) {
                // cast the found value to IntValue
                IntValue foundIndex = (IntValue)index;
                if (semaphoreTbl.containsKey(foundIndex.getValue())) {
                    // use lock to ensure thread safety
                    lock.lock();
                    // retrieving the data from the semaphore table
                    Pair<Integer, ArrayList<Integer>> semValue = semaphoreTbl.get(foundIndex.getValue());
                    Integer N1 = semValue.getKey();
                    ArrayList<Integer> list1 = semValue.getValue();

                    if (list1.contains(state.getId())) {
                        // remove the stateId from the list as it called release
                        list1.remove(Integer.valueOf(state.getId()));
//                        semaphoreTbl.update(foundIndex.getValue(), new Pair<>(N1, list1));
                    }

                    lock.unlock();
                } else throw new CustomException("The found index doesn't exist in Semaphore Table!");
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
    public String toString () {
        return "release(" + this.var + ")";
    }
}
