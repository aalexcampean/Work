package model.types;

import model.values.IValue;

public interface IType {
    IValue defaultValue();
    IType deepCopy();
}
