package model.statements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.IStack;
import model.expressions.IExp;
import model.types.BoolType;
import model.types.IType;
import model.values.BoolValue;
import model.values.IValue;

public class WhileStmt implements IStmt{
    private IExp exp;
    private IStmt whileS;

    public WhileStmt(IExp e, IStmt s) {
        this.exp = e;
        this.whileS = s;
    }

    @Override
    public PrgState execute(PrgState state) {
        IStack<IStmt> stk = state.getExeStack();
        IDictionary<String, IValue> symTbl = state.getSymTable();
        IValue value = this.exp.eval(symTbl, state.getHeap());

        if (value instanceof BoolValue) {
            BoolValue cond = (BoolValue) value;
            if (cond.getValue()) {
                stk.push(this);
                stk.push(this.whileS);
            }

        }
        else {
            throw new CustomException("Conditional expression is not a boolean!");
        }
        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        IType typeExp = this.exp.typeCheck(typeEnv);

        if (typeExp.equals(new BoolType())) {
            this.whileS.typeCheck(typeEnv.deepCopy());
            return typeEnv;
        }
        else
            throw new CustomException("The condition of While doesn't have the type bool!");
    }

    @Override
    public String toString() {
        return "(while (" + this.exp + ") " + this.whileS + ")";
    }
}
