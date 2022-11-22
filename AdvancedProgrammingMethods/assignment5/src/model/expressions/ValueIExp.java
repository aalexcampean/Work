package model.expressions;

import exception.CustomException;
import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.types.BoolType;
import model.types.IntType;
import model.types.StringType;
import model.values.IValue;

public class ValueIExp implements IExp {
    private IValue value;

    public ValueIExp(IValue v) {this.value = v;}

    @Override
    public  IValue eval(IDictionary<String, IValue> symTable, IHeap<IValue> heap) {
        if (!this.value.getType().equals(new IntType()) &&
                !this.value.getType().equals(new BoolType()) && !this.value.getType().equals(new StringType())) {
            throw new CustomException("Unknown type!");
        }
        return this.value;
    }

    @Override
    public String toString() {
        return this.value.toString();
    }

}
