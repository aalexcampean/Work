package model.expressions;

import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.values.IValue;
import model.values.IntValue;

public class ConstIExp implements IExp {
    private int number;

    public void ConstExp(int n) {this.number = n;}

    @Override
    public IValue eval(IDictionary<String, IValue> symTable, IHeap<IValue> heap) {
        return new IntValue(this.number);
    }

    @Override
    public String toString() {return Integer.toString(this.number);}
}
