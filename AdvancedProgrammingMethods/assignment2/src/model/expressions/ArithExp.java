package model.expressions;

import exception.CustomException;
import model.adtContainers.IDictionary;
import model.types.IntType;
import model.values.IValue;
import model.values.IntValue;

public class ArithExp implements Exp {
    Exp exp1, exp2;
    char operator;

    public ArithExp(char op, Exp e1, Exp e2) {
        this.exp1 = e1;
        this.exp2 = e2;
        this.operator = op;
    }

    @Override
    public IValue eval(IDictionary<String, IValue> symTable) throws Exception {
        IValue value1, value2;
        value1 = this.exp1.eval(symTable);
        if (value1.getType().equals(new IntType())) {
            value2 = this.exp2.eval(symTable);
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

    public Exp getFirstExp() {
        return this.exp1;
    }

    public Exp getSecondExp() {
        return this.exp2;
    }

    public String toString() {
        return this.exp1.toString() + " " + this.operator + " " + this.exp2.toString();
    }
}
