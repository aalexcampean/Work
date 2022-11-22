package model.expressions;

import exception.CustomException;
import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.types.IType;
import model.values.IValue;

public class NegExp implements IExp{
    private IExp exp;

    public NegExp(IExp e) {
        String negOp = "";
        RelationalExp relExp = (RelationalExp) e;

        switch (relExp.getOperator()) {
            case "<":
                negOp = ">=";
            case "<=":
                negOp = ">";
            case "==":
                negOp = "!=";
            case "!=":
                negOp = "==";
            case ">":
                negOp = "<=";
            case ">=":
                negOp = "<";
        }
        this.exp = new RelationalExp(relExp.getExp1(), relExp.getExp2(), negOp);
    }

    @Override
    public IValue eval(IDictionary<String, IValue> symTable, IHeap<IValue> heap) {
        return this.exp.eval(symTable, heap);
    }

    @Override
    public IType typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        return this.exp.typeCheck(typeEnv);
    }

    @Override
    public String toString() {
        return "!(" + this.exp.toString() + ")";
    }
}
