package model.statements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.MyList;
import model.expressions.IExp;
import model.types.IType;
import model.values.IValue;

public class PrintStmt implements IStmt{
    private IExp exp;

    public PrintStmt(IExp e){
        this.exp = e;
    }

    @Override
    public PrgState execute(PrgState state) {
        MyList<IValue> out = state.getOut();
        out.add(this.exp.eval(state.getSymTable(), state.getHeap()));
        state.setOut(out);
        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        this.exp.typeCheck(typeEnv);
        return typeEnv;
    }

    @Override
    public String toString(){
        return "print(" + this.exp.toString() + ")";
    }
}
