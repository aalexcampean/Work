package model.statements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.IStack;
import model.expressions.Exp;
import model.types.BoolType;
import model.values.BoolValue;
import model.values.IValue;

public class IfStmt implements IStmt{
    Exp exp;
    IStmt thenS;
    IStmt elseS;

    public IfStmt(Exp e, IStmt t, IStmt el){
        this.exp = e;
        this.thenS = t;
        this.elseS = el;
    }

    @Override
    public PrgState execute(PrgState state) {
        IStack<IStmt> stk = state.getExeStack();
        IDictionary<String, IValue> symTbl = state.getSymTable();
        IValue val = this.exp.eval(symTbl);

        if (val.getType().equals(new BoolType())){
            BoolValue cond = (BoolValue) val;
            if (cond.getValue()) {
                stk.push(this.thenS);
            }
            else {
                stk.push(this.elseS);
            }
        }
        else {
            throw new CustomException("Conditional expression is not a boolean!");
        }
        return state;
    }

    @Override
    public String toString(){
        return "if (" + this.exp.toString() + ") then (" + this.thenS.toString() +
                ") else (" + this.elseS.toString() + ")";
    }
}
