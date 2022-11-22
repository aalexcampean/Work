package model.expressions;

import exception.CustomException;
import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.types.IType;
import model.types.IntType;
import model.values.IValue;
import model.values.IntValue;

public class ArithIExp implements IExp {
    IExp exp1, exp2;
    char operator;

    public ArithIExp(char op, IExp e1, IExp e2) {
        this.exp1 = e1;
        this.exp2 = e2;
        this.operator = op;
    }

    @Override
    public IValue eval(IDictionary<String, IValue> symTable, IHeap<IValue> heap) {
        IValue value1, value2;
        value1 = this.exp1.eval(symTable, heap);
        if (value1.getType().equals(new IntType())) {
            value2 = this.exp2.eval(symTable, heap);
            if (value2.getType().equals(new IntType())) {
                IntValue int1 = (IntValue) value1;
                IntValue int2 = (IntValue) value2;
                int number1, number2;

                number1 = int1.getValue();
                number2 = int2.getValue();

                switch (this.operator) {
                    case '+':
                        return new IntValue(number1 + number2);
                    case '-':
                        return new IntValue(number1 - number2);
                    case '*':
                        return new IntValue(number1 * number2);
                    case '/':
                        if (number2 == 0) {
                            throw new CustomException("Division by 0!");
                        }
                        return new IntValue(number1 / number2);
                }
            } else {
                throw new CustomException("Second operand is not an integer!");
            }
        } else {
            throw new CustomException("First operand is not an integer!");
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
                return new IntType();
            }
            else
                throw new CustomException("Second operand is not an integer!");
        }
        else
            throw new CustomException("First operand is not an integer!");
    }

    public char getOperator() {
        return this.operator;
    }

    public IExp getFirstExp() {
        return this.exp1;
    }

    public IExp getSecondExp() {
        return this.exp2;
    }

    public String toString() {
        return this.exp1.toString() + " " + this.operator + " " + this.exp2.toString();
    }
}
