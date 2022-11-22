package model.types;

import model.values.BoolValue;
import model.values.IValue;


public class BoolType implements IType{
    @Override
    public boolean equals(Object o){
        if (o == null | o.getClass() != this.getClass()){
            return false;
        }
        return true;
    }

    @Override
    public IValue defaultValue() {
        return new BoolValue(false);
    }

    @Override
    public IType deepCopy() {
        return new BoolType();
    }

    @Override
    public String toString(){
        return "bool";
    }
}
