package model.values;

import model.types.IType;
import model.types.StringType;

public class StringValue implements IValue{
    private String value;

    public StringValue() {
        this.value = "";
    }

    public StringValue(String v) {
        this.value = v;
    }

    public String getValue() {
        return this.value;
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || o.getClass() != this.getClass()){
            return false;
        }
        StringValue oValue = (StringValue) o;
        return this.value.equals(oValue.getValue());
    }

    @Override
    public IType getType() {
        return new StringType();
    }

    @Override
    public IValue deepCopy() {
        return new StringValue(this.value);
    }

    @Override
    public String toString() {
        return this.value;
    }
}
