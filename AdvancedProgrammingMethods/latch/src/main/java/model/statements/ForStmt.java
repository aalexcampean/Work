package model.statements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.IStack;
import model.expressions.IExp;
import model.expressions.RelationalExp;
import model.expressions.VarExp;
import model.types.IType;
import model.types.IntType;
import model.values.IValue;

import java.io.IOException;

public class ForStmt implements IStmt{
    private String variable;
    private IExp initialize;
    private IExp condition;
    private IExp increment;
    private IStmt forStmt;

    public ForStmt(String v, IExp initial, IExp cond, IExp inc, IStmt s) {
        this.variable = v;
        this.initialize = initial;
        this.condition = cond;
        this.increment = inc;
        this.forStmt = s;
    }

    @Override
    public PrgState execute(PrgState state) throws IOException {
        IStack<IStmt> stk = state.getExeStack();
        IDictionary<String, IValue> symTbl = state.getSymTable();

        if (symTbl.containsKey(this.variable)) {
            IStmt newStmt = new CompStmt(new AssignStmt(this.variable, this.initialize),
                    new WhileStmt(new RelationalExp(new VarExp(this.variable), this.condition, "<"),
                            new CompStmt(this.forStmt, new AssignStmt(this.variable, this.increment))));
            stk.push(newStmt);
            return null;
        }
        else throw new CustomException("Used variable " + this.variable + " was not declared before!");
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        IType variableType = typeEnv.get(this.variable);
        IType initializeType = this.initialize.typeCheck(typeEnv);
        IType conditionType = this.condition.typeCheck(typeEnv);
        IType incrementType = this.increment.typeCheck(typeEnv);

        if (variableType.equals(new IntType()))
            if (initializeType.equals(new IntType()))
                if (conditionType.equals(new IntType()))
                    if (incrementType.equals(new IntType()))
                        return typeEnv;

                    else throw new CustomException("The increment value used in the ForStmt doesn't have the type bool!");
                else throw new CustomException("The condition used in the ForStmt doesn't have the type bool!");
            else throw new CustomException("The initial value assigned to the variable in the ForStmt doesn't have the type bool!");
        else throw new CustomException("The variable used in the ForStmt doesn't have the type bool!");
    }

    @Override
    public String toString() {
        return "for(" + this.variable + " = " + this.initialize.toString() + "; " + this.variable + " < " + this.condition.toString() + "; " + this.variable + " = " + this.increment.toString() + ")\n" + this.forStmt.toString();
    }
}
