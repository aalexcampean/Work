package model.expressions;

import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.values.IValue;

public interface IExp {
     IValue eval(IDictionary<String, IValue> symTable, IHeap<IValue> heap);
}
