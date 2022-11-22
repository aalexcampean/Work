package model.heapExpressions;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.expressions.IExp;
import model.statements.IStmt;
import model.values.IValue;
import model.values.RefValue;

public class HeapReadingExp implements IExp {
    private IExp exp;

    public HeapReadingExp(IExp e) {
        this.exp = e;
    }

    @Override
    public IValue eval(IDictionary<String, IValue> symTable, IHeap<IValue> heap) {
        IValue value = exp.eval(symTable, heap);
        if (value instanceof RefValue) {
            int key = ((RefValue) value).getAddress();
            if (heap.containsKey(key)) {
                return heap.get(key);
            }
            throw new CustomException("The Heap does not contain that key!");
        }
        throw new CustomException("The evaluated expression is not of type RefValue!");
    }

    @Override
    public String toString() {
        return "rH(" + this.exp.toString() + ")";
    }
}
