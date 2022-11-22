package model.statements;

import model.PrgState;

public class NopStmt implements IStmt{
    @Override
    public PrgState execute(PrgState state) {
        return null;
    }

    @Override
    public String toString(){return "No operation!";}
}
