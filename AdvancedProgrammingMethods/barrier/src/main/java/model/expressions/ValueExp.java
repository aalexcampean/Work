package model.expressions;

import exception.CustomException;
import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.types.BoolType;
import model.types.IType;
import model.types.IntType;
import model.types.StringType;
import model.values.IValue;

public class ValueExp implements IExp {
    private IValue value;

    public ValueExp(IValue v) {this.value = v;}

    @Override
    public  IValue eval(IDictionary<String, IValue> symTable, IHeap<IValue> heap) {
        if (!this.value.getType().equals(new IntType()) &&
                !this.value.getType().equals(new BoolType()) && !this.value.getType().equals(new StringType())) {
            throw new CustomException("Unknown type!");
        }
        return this.value;
    }

    @Override
    public IType typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        return this.value.getType();
    }

    @Override
    public String toString() {
        return this.value.toString();
    }

}
