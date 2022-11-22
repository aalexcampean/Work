package model.statements;

import exception.CustomException;
import model.PrgState;

public interface IStmt {
    public PrgState execute(PrgState state) throws Exception;
}
