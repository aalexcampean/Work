package model.expressions;

import exception.CustomException;
import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.types.BoolType;
import model.types.IType;
import model.values.BoolValue;
import model.values.IValue;

public class LogicExp implements IExp {
    IExp exp1, exp2;
    String operator;

    public LogicExp(String op, IExp ex1, IExp ex2){
        this.operator = op;
        this.exp1 = ex1;
        this.exp2 = ex2;
    }

    @Override
    public IValue eval(IDictionary<String, IValue> symTable, IHeap<IValue> heap) {
        IValue value1, value2;
        value1 = this.exp1.eval(symTable, heap);
        if (value1.getType().equals(new BoolType())) {
            value2 = this.exp2.eval(symTable, heap);
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
    public IType typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        IType type1, type2;
        type1 = exp1.typeCheck(typeEnv);
        type2 = exp2.typeCheck(typeEnv);

        if (type1.equals(new BoolType())) {
            if (type2.equals(new BoolType())) {
                return new BoolType();
            }
            else
                throw new CustomException("Second operand is not a boolean!");
        }
        else
            throw new CustomException("First operand is not a boolean!");
    }

    @Override
    public String toString() {
        return this.exp1.toString() + " " + this.operator + " " + this.exp2.toString();
    }
}
