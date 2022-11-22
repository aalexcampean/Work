package model.expressions;

import exception.CustomException;
import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.types.IType;
import model.values.IValue;

public class VarIExp implements IExp {
    String id;

    public VarIExp(String id) {this.id = id;}

    public IValue eval(IDictionary<String, IValue> symTable, IHeap<IValue> heap) {
        if (symTable.containsKey(this.id)) {
            return symTable.get(this.id);
        }
        else {
            throw new CustomException("Variable " + this.id + " is not defined");
        }

    }

    @Override
    public IType typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        return typeEnv.get(this.id);
    }

    public String toString() {return this.id;}
}
