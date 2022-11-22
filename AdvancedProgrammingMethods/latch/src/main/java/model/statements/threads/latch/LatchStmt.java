package model.statements.threads.latch;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.adtContainers.ILatch;
import model.expressions.IExp;
import model.statements.IStmt;
import model.types.IType;
import model.types.IntType;
import model.values.IValue;
import model.values.IntValue;

import java.io.IOException;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class LatchStmt implements IStmt {
    private String var;
    private IExp exp;
    private static Lock lock = new ReentrantLock();

    public LatchStmt(String v, IExp e) {
        this.var = v;
        this.exp = e;
    }

    @Override
    public PrgState execute(PrgState state) throws IOException {
        IDictionary<String, IValue> symTbl = state.getSymTable();
        IHeap<IValue> heap = state.getHeap();
        ILatch latchTbl = state.getLatchTbl();

        IValue number1 = this.exp.eval(symTbl, heap);
        if (number1.getType().equals(new IntType())) {
            lock.lock();
            Integer value = ((IntValue) number1).getValue();
            IntValue location = new IntValue(state.getLatchTbl().getFreeAddress());

            latchTbl.add(value);
            if (symTbl.containsKey(this.var)) {
                symTbl.update(this.var, location);
            } else symTbl.add(this.var, location);

            lock.unlock();
        } else throw new CustomException("The evaluated expression is not of IntType!");

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
        return "latch(" + this.var + ", " + this.exp.toString() + ")";
    }
}
