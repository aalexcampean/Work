package model.statements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.expressions.Exp;
import model.types.IType;
import model.values.IValue;

public class VarDeclStmt implements IStmt{
    private String id;
    private IType type;

    public VarDeclStmt(String i, IType t){
        this.id = i;
        this.type = t;
    }

    @Override
    public PrgState execute(PrgState state) {
        IDictionary<String, IValue> symTbl = state.getSymTable();
        if (symTbl.containsKey(this.id)){
            throw new CustomException("Variable already defined!");
        }
        symTbl.add(this.id, this.type.defaultValue());
        return state;
    }

    @Override
    public String toString(){
        return this.type + " " + this.id;
    }
}
