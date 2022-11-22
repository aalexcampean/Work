package model.expressions;

import exception.CustomException;
import model.adtContainers.IDictionary;
import model.values.IValue;

public interface Exp {
     IValue eval(IDictionary<String, IValue> symTable);
}
