package model.statements;

import model.PrgState;
import model.adtContainers.MyList;
import model.expressions.IExp;
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
    public String toString(){
        return "print(" + this.exp.toString() + ")";
    }
}
