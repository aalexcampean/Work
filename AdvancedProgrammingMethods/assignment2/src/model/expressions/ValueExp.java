package model.expressions;

import exception.CustomException;
import model.adtContainers.IDictionary;
import model.types.BoolType;
import model.types.IntType;
import model.values.IValue;

public class ValueExp implements Exp{
    private IValue value;

    public ValueExp(IValue v) {this.value = v;}

    @Override
    public  IValue eval(IDictionary<String, IValue> symTable) throws Exception {
        if (!this.value.getType().equals(new IntType()) && !this.value.getType().equals(new BoolType())) {
            throw new CustomException("Unknown type!");
        }
        return this.value;
    }

    @Override
    public String toString() {
        return this.value.toString();
    }

}