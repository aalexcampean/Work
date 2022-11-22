package model.expressions;

import exception.CustomException;
import model.adtContainers.IDictionary;
import model.types.BoolType;
import model.values.BoolValue;
import model.values.IValue;
import model.values.IntValue;

public class LogicExp implements Exp{
    Exp exp1, exp2;
    String operator;

    public LogicExp(String op, Exp ex1, Exp ex2){
        this.operator = op;
        this.exp1 = ex1;
        this.exp2 = ex2;
    }

    @Override
    public IValue eval(IDictionary<String, IValue> symTable) throws Exception {
        IValue value1, value2;
        value1 = this.exp1.eval(symTable);
        if (value1.getType().equals(new BoolType())) {
            value2 = this.exp2.eval(symTable);
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
        return this.exp1.toString() + " " + this.operator + " " + this.exp2.toString();
    }
}
