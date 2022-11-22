package model.statements;

import model.PrgState;
import model.adtContainers.MyList;
import model.expressions.Exp;
import model.values.IValue;

public class PrintStmt implements IStmt{
    private Exp exp;

    public PrintStmt(Exp e){
        this.exp = e;
    }

    @Override
    public PrgState execute(PrgState state) {
        MyList<IValue> out = state.getOut();
        out.add(this.exp.eval(state.getSymTable()));
        state.setOut(out);
        return state;
    }

    @Override
    public String toString(){
        return "(" + this.exp.toString() + ")";
    }
}
