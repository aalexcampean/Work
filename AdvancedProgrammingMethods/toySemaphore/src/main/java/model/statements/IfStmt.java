package model.statements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.IStack;
import model.expressions.IExp;
import model.types.BoolType;
import model.types.IType;
import model.values.BoolValue;
import model.values.IValue;

public class IfStmt implements IStmt{
    IExp exp;
    IStmt thenS;
    IStmt elseS;

    public IfStmt(IExp e, IStmt t, IStmt el){
        this.exp = e;
        this.thenS = t;
        this.elseS = el;
    }

    @Override
    public PrgState execute(PrgState state) {
        IStack<IStmt> stk = state.getExeStack();
        IDictionary<String, IValue> symTbl = state.getSymTable();
        IValue val = this.exp.eval(symTbl, state.getHeap());

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
        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        IType typeExp = this.exp.typeCheck(typeEnv);

        if (typeExp.equals(new BoolType())) {
            this.thenS.typeCheck(typeEnv.deepCopy());
            this.elseS.typeCheck(typeEnv.deepCopy());
            return typeEnv;
        }
        else
            throw new CustomException("The condition of If doesn't have the type bool!");
    }

    @Override
    public String toString(){
        return "if (" + this.exp.toString() + ") then (" + this.thenS.toString() +
                ") else (" + this.elseS.toString() + ")";
    }
}