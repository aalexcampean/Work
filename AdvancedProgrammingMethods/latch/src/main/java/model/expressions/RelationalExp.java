package model.expressions;

import exception.CustomException;
import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.types.BoolType;
import model.types.IType;
import model.types.IntType;
import model.values.BoolValue;
import model.values.IValue;
import model.values.IntValue;

public class RelationalExp implements IExp {
    private IExp exp1, exp2;
    private String operator;

    public RelationalExp(IExp e1, IExp e2, String op) {
        this.exp1 = e1;
        this.exp2 = e2;
        this.operator = op;
    }

    public IExp getExp1() {return this.exp1;}
    public IExp getExp2() {return this.exp2;}
    public String getOperator() {return this.operator;}

    @Override
    public IValue eval(IDictionary<String, IValue> symTable, IHeap<IValue> heap) {
        IValue value1, value2;
        value1 = this.exp1.eval(symTable, heap);
        if (value1.getType().equals(new IntType())) {
            value2 = this.exp2.eval(symTable, heap);
            if (value2.getType().equals(new IntType())) {
                IntValue int1 = (IntValue) value1;
                IntValue int2 = (IntValue) value2;
                int b1, b2;

                b1 = int1.getValue();
                b2 = int2.getValue();

                switch (operator) {
                    case "<":
                        return new BoolValue(b1 < b2);
                    case "<=":
                        return new BoolValue(b1 <= b2);
                    case "==":
                        return new BoolValue(b1 == b2);
                    case "!=":
                        return new BoolValue(b1 != b2);
                    case ">":
                        return new BoolValue(b1 > b2);
                    case ">=":
                        return new BoolValue(b1 >= b2);
                }
            }
            else {
                throw new CustomException("Second operand is not a int!");
            }
        }
        else {
            throw new CustomException("First operand is not a int!");
        }
        return null;
    }

    @Override
    public IType typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        IType type1, type2;
        type1 = exp1.typeCheck(typeEnv);
        type2 = exp2.typeCheck(typeEnv);

        if (type1.equals(new IntType())) {
            if (type2.equals(new IntType())) {
                return new BoolType();
            }
            else
                throw new CustomException("Second operand is not an integer!");
        }
        else
            throw new CustomException("First operand is not an integer!");
    }

    @Override
    public String toString() {
        return this.exp1.toString() + " " + this.operator + " " + this.exp2.toString();
    }
}
