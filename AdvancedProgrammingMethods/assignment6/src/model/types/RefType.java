package model.types;

import model.values.IValue;
import model.values.RefValue;

public class RefType implements IType{
    IType inner;

    public RefType() {
        this.inner = null;
    }

    public RefType(IType givenInner) {
        this.inner = givenInner;
    }

    public IType getInner() {
        return this.inner;
    }

    @Override
    public boolean equals(Object o) {
        if (o instanceof RefType) {
            return this.inner.equals(((RefType) o).getInner());
//            return true;
        }
        return false;
    }

    @Override
    public IValue defaultValue() {
        return new RefValue(0, this.inner);
    }

    @Override
    public IType deepCopy() {
        return new RefType(this.inner);
    }

    @Override
    public String toString() {
        return "Ref(" + this.inner.toString() + ")";
    }
}
