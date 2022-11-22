package model.expressions;

import exception.CustomException;
import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.types.IntType;
import model.values.IValue;
import model.values.IntValue;

public class ArithIExp implements IExp {
    IExp IExp1, IExp2;
    char operator;

    public ArithIExp(char op, IExp e1, IExp e2) {
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

    public char getOperator() {
        return this.operator;
    }

    public IExp getFirstExp() {
        return this.IExp1;
    }

    public IExp getSecondExp() {
        return this.IExp2;
    }

    public String toString() {
        return this.IExp1.toString() + " " + this.operator + " " + this.IExp2.toString();
    }
}
