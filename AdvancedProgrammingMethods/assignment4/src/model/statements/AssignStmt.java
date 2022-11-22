package model.statements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.IStack;
import model.expressions.IExp;
import model.types.IType;
import model.values.IValue;

public class AssignStmt implements IStmt{
    private String id;
    IExp exp;

    public AssignStmt(String i, IExp e) {
        this.id = i;
        this.exp = e;
    }

    @Override
    public PrgState execute(PrgState state) {
        IStack<IStmt> stk = state.getExeStack();
        IDictionary<String, IValue> symTbl = state.getSymTable();

        if (symTbl.containsKey(this.id)) {
            IValue val = this.exp.eval(symTbl, state.getHeap());
            IType typeId = (symTbl.get(this.id)).getType();

            if (val.getType().equals(typeId)){
                symTbl.update(this.id, val);
            }
            else {
                throw new CustomException("Declared type of variable " + this.id + " and type of assigned expression don't match!");
            }
        }
        else {
            throw new CustomException("Used variable " + this.id + " was not declared before!");
        }
        return state;
    }

    @Override
    public String toString(){
        return this.id + " = " + this.exp.toString();
    }
}
