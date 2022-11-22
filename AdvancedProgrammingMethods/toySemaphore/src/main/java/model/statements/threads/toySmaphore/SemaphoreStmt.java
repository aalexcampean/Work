package model.statements.threads.toySmaphore;

import exception.CustomException;
import javafx.util.Pair;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.adtContainers.ISemaphore;
import model.adtContainers.MyTriplet;
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

public class SemaphoreStmt implements IStmt {
    private String var;
    private IExp exp1;
    private IExp exp2;
    private static Lock lock = new ReentrantLock();

    public SemaphoreStmt(String v, IExp e1, IExp e2) {
        this.var = v;
        this.exp1 = e1;
        this.exp2 = e2;
    }

    @Override
    public PrgState execute(PrgState state) throws IOException {
        IDictionary<String, IValue> symTbl = state.getSymTable();
        IHeap<IValue> heap = state.getHeap();
        ISemaphore semaphoreTbl = state.getSemaphoreTbl();

        if (symTbl.containsKey(this.var)){
            IValue number1 = this.exp1.eval(symTbl, heap);
            IValue number2 = this.exp2.eval(symTbl, heap);
            if (number1.getType().equals(new IntType()) && number2.getType().equals(new IntType())) {
                lock.lock();
                Integer value1 = ((IntValue)number1).getValue();
                Integer value2 = ((IntValue)number2).getValue();
                IntValue location = new IntValue(state.getSemaphoreTbl().getFreeAddress());

                semaphoreTbl.add(new MyTriplet<>(value1, new ArrayList<>(), value2));
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

        if (!this.exp1.typeCheck(typeEnv).equals(new IntType()))
            throw new CustomException("Expression not of IntType!");

        if (!this.exp2.typeCheck(typeEnv).equals(new IntType()))
            throw new CustomException("Expression not of IntType!");

        return typeEnv;
    }

    @Override
    public String toString() {
        return "semaphore(" + this.var + ", " + this.exp1.toString() + ", " + this.exp2.toString() + ")";
    }
}
