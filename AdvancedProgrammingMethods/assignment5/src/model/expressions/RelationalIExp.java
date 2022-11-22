package model.expressions;

import exception.CustomException;
import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.types.IntType;
import model.values.BoolValue;
import model.values.IValue;
import model.values.IntValue;

public class RelationalIExp implements IExp {
    IExp IExp1, IExp2;
    String operator;

    public RelationalIExp(IExp e1, IExp e2, String op) {
        this.IExp1 = e1;
        this.IExp2 = e2;
        this.operator = op;
    }

    @Override
    public IValue eval(IDictionary<String, IValue> symTable, IHeap<IValue> heap) {
        IValue value1, value2;
        value1 = this.IExp1.eval(symTable, heap);
        if (value1.getType().equals(new IntType())) {
            value2 = this.IExp2.eval(symTable, heap);
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
        return this.IExp1.toString() + " " + this.operator + " " + this.IExp2.toString();
    }
}
