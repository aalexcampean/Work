package model.values;

import model.types.BoolType;
import model.types.IType;


public class BoolValue implements IValue{
    private boolean value;

    public BoolValue(){
        this.value = false;
    }

    public BoolValue(boolean v){
        this.value = v;
    }

    public boolean getValue(){
        return this.value;
    }

    @Override
    public boolean equals(Object o){
        if (o == null || o.getClass() != this.getClass()){
            return false;
        }
        BoolValue oValue = (BoolValue) o;
        return this.value == oValue.getValue();
    }

    @Override
    public IType getType() {
        return new BoolType();
    }

    @Override
    public IValue deepCopy() {
        return new BoolValue(this.value);
    }

    @Override
    public String toString(){
        return Boolean.toString(this.value);
    }
}
