package model.statements;

import model.PrgState;

public interface IStmt {
    public PrgState execute(PrgState state);
}
