package model.statements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.IStack;
import model.expressions.IExp;
import model.types.BoolType;
import model.types.IType;
import model.values.IValue;

import java.io.IOException;

public class CondAssignStmt implements IStmt{
    private String variable;
    private IExp condition;
    private IExp exp1;
    private IExp exp2;

    public CondAssignStmt(String v, IExp c, IExp e1, IExp e2) {
        this.variable = v;
        this.condition = c;
        this.exp1 = e1;
        this.exp2 = e2;
    }

    @Override
    public PrgState execute(PrgState state) throws IOException {
        IStack<IStmt> stk = state.getExeStack();
        IDictionary<String, IValue> symTbl = state.getSymTable();

        if (symTbl.containsKey(this.variable)) {
            IStmt newStmt = new IfStmt(this.condition, new AssignStmt(this.variable, this.exp1), new AssignStmt(this.variable, this.exp2));
            stk.push(newStmt);
            return null;
        }
        else throw new CustomException("Used variable " + this.variable + " was not declared before!");
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        IType typeVar = typeEnv.get(this.variable);
        IType typeCondition = this.condition.typeCheck(typeEnv);
        IType typeExp1 = this.exp1.typeCheck(typeEnv);
        IType typeExp2 = this.exp2.typeCheck(typeEnv);

        if (typeCondition.equals(new BoolType()))
            if (typeVar.equals(typeExp1) && typeVar.equals(typeExp2))
                return typeEnv;
            else throw new CustomException("The values assigned in the CondAssignStmt are not of the same type with the variable!");
        else throw new CustomException("The condition of CondAssignStmt is not of BoolType!");
    }

    @Override
    public String toString() {
        return this.variable + " = " + this.condition.toString() + "? " + this.exp1.toString() + " : " + this.exp2.toString();
    }
}
