package model.statements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.MyDictionary;
import model.types.IType;

import java.io.IOException;

public interface IStmt {
    public PrgState execute(PrgState state) throws IOException;
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws CustomException;
}
