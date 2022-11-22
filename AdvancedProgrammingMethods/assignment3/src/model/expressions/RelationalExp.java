package model.expressions;

import exception.CustomException;
import model.adtContainers.IDictionary;
import model.types.BoolType;
import model.types.IntType;
import model.values.BoolValue;
import model.values.IValue;
import model.values.IntValue;

public class RelationalExp implements Exp{
    Exp exp1, exp2;
    String operator;

    public RelationalExp(Exp e1, Exp e2, String op) {
        this.exp1 = e1;
        this.exp2 = e2;
        this.operator = op;
    }

    @Override
    public IValue eval(IDictionary<String, IValue> symTable) {
        IValue value1, value2;
        value1 = this.exp1.eval(symTable);
        if (value1.getType().equals(new IntType())) {
            value2 = this.exp2.eval(symTable);
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
    public String toString() {
        return this.exp1.toString() + " " + this.operator + " " + this.exp2.toString();
    }
}
