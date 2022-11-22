package model.statements.threads.semaphore;

import exception.CustomException;
import javafx.util.Pair;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.adtContainers.ISemaphore;
import model.expressions.IExp;
import model.statements.IStmt;
import model.types.IType;
import model.types.IntType;
import model.values.IValue;
import model.values.IntValue;

import java.io.IOException;
import java.util.ArrayList;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class CreateSemaphoreStmt implements IStmt {
    private String var;
    private IExp exp;
    private static Lock lock = new ReentrantLock();

    public CreateSemaphoreStmt(String v, IExp e) {
        this.var = v;
        this.exp = e;
    }

    @Override
    public PrgState execute(PrgState state) throws IOException {
        IDictionary<String, IValue> symTbl = state.getSymTable();
        IHeap<IValue> heap = state.getHeap();
        ISemaphore semaphoreTbl = state.getSemaphoreTbl();

        if (symTbl.containsKey(this.var)){
            IValue number1 = this.exp.eval(symTbl, heap);
            if (number1.getType().equals(new IntType())) {
                // use lock to ensure thread safety
                lock.lock();
                Integer value = ((IntValue)number1).getValue();
                // get the next free address in the semaphore table
                IntValue location = new IntValue(state.getSemaphoreTbl().getFreeAddress());

                // add a new entry in the semaphore table
                semaphoreTbl.add(new Pair<>(value, new ArrayList<>()));
                // update the symbolTable accordingly (update de value associated to the var)
                symTbl.update(this.var, location);
                lock.unlock();
            }
            else throw new CustomException("The evaluated expression is not of IntType!");
        } else throw new CustomException("Variable is undefined!");

        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        if (!typeEnv.containsKey(this.var))
            throw new CustomException("Variable is not defined!");

        if (!typeEnv.get(this.var).equals(new IntType()))
            throw new CustomException("Variable not of IntType!");

        if (!this.exp.typeCheck(typeEnv).equals(new IntType()))
            throw new CustomException("Expression not of IntType!");

        return typeEnv;
    }

    @Override
    public String toString() {
        return "createSemaphore(" + this.var + ", " + this.exp.toString() + ")";
    }
}
