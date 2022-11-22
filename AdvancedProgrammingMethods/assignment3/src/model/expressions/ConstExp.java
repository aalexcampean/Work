package model.expressions;

import exception.CustomException;
import model.adtContainers.IDictionary;
import model.values.IValue;
import model.values.IntValue;

public class ConstExp implements Exp{
    private int number;

    public void ConstExp(int n) {this.number = n;}

    @Override
    public IValue eval(IDictionary<String, IValue> symTable) {
        return new IntValue(this.number);
    }

    @Override
    public String toString() {return Integer.toString(this.number);}
}
