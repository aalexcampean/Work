package model.statements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.IStack;
import model.expressions.IExp;
import model.values.BoolValue;
import model.values.IValue;

public class WhileStmt implements IStmt{
    IExp exp;
    IStmt whileS;

    public WhileStmt(IExp e, IStmt s) {
        this.exp = e;
        this.whileS = s;
    }

    @Override
    public PrgState execute(PrgState state) {
        IStack<IStmt> stk = state.getExeStack();
        IDictionary<String, IValue> symTbl = state.getSymTable();
        IValue value = this.exp.eval(symTbl, state.getHeap());

        if (value instanceof BoolValue) {
            BoolValue cond = (BoolValue) value;
            if (cond.getValue()) {
                stk.push(this);
                stk.push(this.whileS);
            }

        }
        else {
            throw new CustomException("Conditional expression is not a boolean!");
        }
        return null;
    }

    @Override
    public String toString() {
        return "(while (" + this.exp + ") " + this.whileS + ")";
    }
}
