package model.statements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.adtContainers.IStack;
import model.expressions.IExp;
import model.types.BoolType;
import model.types.IType;
import model.values.IValue;
import model.values.IntValue;

import java.io.IOException;

public class SwitchStmt implements IStmt{
    private IExp condition;
    private IExp case1;
    private IStmt stmt1;
    private IExp case2;
    private IStmt stmt2;
    private IStmt stmt3;

    public SwitchStmt(IExp c, IExp c1, IStmt s1, IExp c2, IStmt s2, IStmt s3) {
        this.condition = c;
        this.case1 = c1;
        this.case2 = c2;
        this.stmt1 = s1;
        this.stmt2 = s2;
        this.stmt3 = s3;
    }

    @Override
    public PrgState execute(PrgState state) throws IOException {
        IStack<IStmt> stk = state.getExeStack();
        IDictionary<String, IValue> symTbl = state.getSymTable();
        IHeap<IValue> heap = state.getHeap();

        IValue exp = this.condition.eval(symTbl, heap);
        Integer intExp = ((IntValue) exp).getValue();

        IValue exp1 = this.case1.eval(symTbl, heap);
        Integer intExp1 = ((IntValue) exp1).getValue();

        IValue exp2 = this.case2.eval(symTbl, heap);
        Integer intExp2 = ((IntValue) exp2).getValue();

        IStmt newStmt;
        if (intExp.equals(intExp1))
            newStmt = stmt1;
        else if (intExp.equals(intExp2))
            newStmt = stmt2;
        else newStmt = stmt3;

        stk.push(newStmt);
        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        IType typeCondition = this.condition.typeCheck(typeEnv);
        IType typeCase1 = this.case1.typeCheck(typeEnv);
        IType typeCase2 = this.case2.typeCheck(typeEnv);

        if (typeCondition.equals(typeCase1) && typeCondition.equals(typeCase2)) {
            // typechecking the statements
            this.stmt1.typeCheck(typeEnv.deepCopy());
            this.stmt2.typeCheck(typeEnv.deepCopy());
            this.stmt3.typeCheck(typeEnv.deepCopy());
            return typeEnv;
        }
        else
            throw new CustomException("The condition of the SwitchStmt does not have the same type with the cases!");
    }

    @Override
    public String toString() {
        return "switch(" + this.condition.toString() + ")" + "\n(case " + this.case1.toString() + ": " + this.stmt1.toString() + ")" +
                "\n(case " + this.case2.toString() + ": " + this.stmt2.toString() + ")" + "\n(default : " + this.stmt3.toString() + ")";
    }
}
