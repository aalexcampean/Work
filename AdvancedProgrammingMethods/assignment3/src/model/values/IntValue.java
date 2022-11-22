package model.values;

import model.types.IType;
import model.types.IntType;


public class IntValue implements IValue{
    private int value;

    public IntValue(){
        this.value = 0;
    }

    public IntValue(int v){
        this.value = v;
    }

    public int getValue(){
        return this.value;
    }

    @Override
    public boolean equals(Object o){
        if (o == null || o.getClass() != this.getClass()){
            return false;
        }
        IntValue oValue = (IntValue) o;
        return this.value == oValue.getValue();
    }

    @Override
    public IType getType() {
        return new IntType();
    }

    @Override
    public IValue deepCopy() {
        return new IntValue(this.value);
    }

    @Override
    public String toString(){
        return Integer.toString(this.value);
    }
}
