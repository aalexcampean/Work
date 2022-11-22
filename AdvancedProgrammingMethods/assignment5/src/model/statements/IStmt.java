package model.statements;

import model.PrgState;

import java.io.IOException;

public interface IStmt {
    public PrgState execute(PrgState state) throws IOException;
}
