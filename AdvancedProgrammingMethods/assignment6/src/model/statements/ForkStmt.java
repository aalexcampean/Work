package model.statements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.IStack;
import model.adtContainers.MyStack;
import model.types.BoolType;
import model.types.IType;

public class ForkStmt implements IStmt{
    private IStmt stmt;

    public ForkStmt(IStmt s) {
        this.stmt = s;
    }

    @Override
    public PrgState execute(PrgState state) {
        IStack<IStmt> newExeStack = new MyStack<IStmt>();
//        newExeStack.push(this.stmt);

        return new PrgState(newExeStack, state.getSymTable().deepCopy(), state.getOut(), this.stmt, state.getFileTable(), state.getHeap());
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        this.stmt.typeCheck(typeEnv.deepCopy());
        return typeEnv;
    }

    @Override
    public String toString() {
        return "fork(" + this.stmt.toString() + ")";
    }
}
