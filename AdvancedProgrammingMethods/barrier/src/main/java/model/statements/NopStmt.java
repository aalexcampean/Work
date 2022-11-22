package model.statements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.types.IType;

public class NopStmt implements IStmt{
    @Override
    public PrgState execute(PrgState state) {
        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        return typeEnv;
    }

    @Override
    public String toString(){return "No operation!";}
}
