package model.expressions;

import exception.CustomException;
import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.types.BoolType;
import model.values.BoolValue;
import model.values.IValue;

public class LogicIExp implements IExp {
    IExp IExp1, IExp2;
    String operator;

    public LogicIExp(String op, IExp ex1, IExp ex2){
        this.operator = op;
        this.IExp1 = ex1;
        this.IExp2 = ex2;
    }

    @Override
    public IValue eval(IDictionary<String, IValue> symTable, IHeap<IValue> heap) {
        IValue value1, value2;
        value1 = this.IExp1.eval(symTable, heap);
        if (value1.getType().equals(new BoolType())) {
            value2 = this.IExp2.eval(symTable, heap);
            if (value2.getType().equals(new BoolType())) {
                BoolValue bool1 = (BoolValue) value1;
                BoolValue bool2 = (BoolValue) value2;
                boolean b1, b2;

                b1 = bool1.getValue();
                b2 = bool2.getValue();

                switch (operator) {
                    case "and":
                        return new BoolValue(b1 && b2);
                    case "or":
                        return new BoolValue(b1 || b2);
                }
            }
            else {
                throw new CustomException("Second operand is not a boolean!");
            }
        }
        else {
            throw new CustomException("First operand is not a boolean!");
        }
        return null;
    }

    @Override
    public String toString() {
        return this.IExp1.toString() + " " + this.operator + " " + this.IExp2.toString();
    }
}
