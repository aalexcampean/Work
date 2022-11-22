package model.statements.threads.barrier;

import exception.CustomException;
import javafx.util.Pair;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.IBarrier;
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

public class AwaitBarrierStmt implements IStmt {
    private String var;
    private static Lock lock = new ReentrantLock();

    public AwaitBarrierStmt(String v) {
        this.var = v;
    }

    @Override
    public PrgState execute(PrgState state) throws IOException {
        IStack<IStmt> stk = state.getExeStack();
        IDictionary<String, IValue> symTbl = state.getSymTable();
        IBarrier barrierTbl = state.getBarrierTbl();

        if (symTbl.containsKey(this.var)){
            IValue index = symTbl.get(this.var);
            if (index.getType().equals(new IntType())) {
                IntValue foundIndex = (IntValue)index;
                if (barrierTbl.containsKey(foundIndex.getValue())) {
                    lock.lock();
                    // retrieving the data from the barrier table
                    Pair<Integer, ArrayList<Integer>> barValue = barrierTbl.get(foundIndex.getValue());
                    Integer N1 = barValue.getKey();
                    ArrayList<Integer> list1 = barValue.getValue();
                    Integer NL = list1.size();

                    if (N1 > NL) {
                        if (!list1.contains(state.getId())) {
                            list1.add(state.getId());
//                            barrierTbl.update(foundIndex.getValue(), new Pair<>(N1, list1));
                        }
                        stk.push(this);
                    }

                    lock.unlock();
                } else throw new CustomException("The found index doesn't exist in Barrier Table!");
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
        return "await(" + this.var + ")";
    }
}
