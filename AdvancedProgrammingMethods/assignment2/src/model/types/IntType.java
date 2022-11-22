package model.types;

import model.values.IValue;
import model.values.IntValue;

public class IntType implements IType{

    @Override
    public boolean equals(Object o){
        if (o == null | o.getClass() != this.getClass()){
            return false;
        }
        return true;
    }

    @Override
    public IValue defaultValue() {
        return new IntValue(0);
    }

    @Override
    public IType deepCopy() {
        return new IntType();
    }

    @Override
    public String toString(){
        return "int";
    }
}
