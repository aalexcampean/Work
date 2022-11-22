package model.statements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.IStack;
import model.types.IType;

public class CompStmt implements IStmt{
    private IStmt first;
    private IStmt second;

    public CompStmt(IStmt f, IStmt s){
        this.first = f;
        this.second = s;
    }

    public IStmt getFirst(){
        return this.first;
    }

    public IStmt getSecond(){
        return this.second;
    }

    @Override
    public PrgState execute(PrgState state) {
        IStack<IStmt> stk = state.getExeStack();
        stk.push(this.second);
        stk.push(this.first);
        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        // IDictionary<String,Type> typEnv1 = this.first.typeCheck(typeEnv);
        // IDictionary<String,Type> typEnv2 = this.second.typeCheck(typEnv1);
        // return typEnv2;
        return this.second.typeCheck(this.first.typeCheck(typeEnv));
    }

    @Override
    public String toString(){
        return "(" + this.first.toString() + ";" +this.second.toString() + ")";
    }
}
