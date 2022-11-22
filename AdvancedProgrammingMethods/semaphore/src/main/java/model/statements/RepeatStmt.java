package model.statements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.IStack;
import model.expressions.IExp;
import model.expressions.NegExp;
import model.types.IType;

import java.io.IOException;

public class RepeatStmt implements IStmt{
    private IStmt repeatStmt;
    private IExp condition;

    public RepeatStmt(IStmt rs, IExp c) {
        this.repeatStmt = rs;
        this.condition = c;
    }

    @Override
    public PrgState execute(PrgState state) throws IOException {
        IStack<IStmt> stk = state.getExeStack();
        IStmt newStmt = new CompStmt(this.repeatStmt, new WhileStmt(new NegExp(this.condition), this.repeatStmt));
        stk.push(newStmt);
        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "repeat(" + this.repeatStmt.toString() + ") " + "until " + this.condition.toString();
    }
}
