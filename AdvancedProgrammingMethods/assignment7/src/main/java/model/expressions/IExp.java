package model.expressions;

import exception.CustomException;
import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.types.IType;
import model.values.IValue;

import java.lang.reflect.Type;

public interface IExp {
     IValue eval(IDictionary<String, IValue> symTable, IHeap<IValue> heap);
     IType typeCheck(IDictionary<String, IType> typeEnv) throws CustomException;
}
