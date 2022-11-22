package model.heapStatements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.expressions.IExp;
import model.statements.IStmt;
import model.types.RefType;
import model.values.IValue;
import model.values.RefValue;

public class HeapWritingStmt implements IStmt {
    private String var_name;
    private IExp exp;

    public HeapWritingStmt(String vn, IExp e) {
        this.var_name = vn;
        this.exp = e;
    }

    @Override
    public PrgState execute(PrgState state) {
        IDictionary<String, IValue> symTbl = state.getSymTable();
        IHeap<IValue> heap = state.getHeap();

        if (symTbl.containsKey(this.var_name)) {
            IValue value = symTbl.get(this.var_name);
            if (value.getType() instanceof RefType) {
                int key = ((RefValue) value).getAddress();
                if (heap.containsKey(key)) {
                    IValue secondValue = this.exp.eval(symTbl, heap);
                    if (secondValue.getType().equals(((RefValue) value).getLocationType())) {
                        heap.update(key, secondValue);
                        return state;
                    }
                    throw new CustomException("Types do not coincide!");
                }
                throw new CustomException("The Heap does not contain that key!");
            }
            throw new CustomException("The variable associated to the provided VarName is not of type RefType");
        }
        throw new CustomException("VarName notfound in SymbolTable!");
    }

    @Override
    public String toString() {return "heapWrite(" + this.var_name + " " + this.exp.toString() + ")";}
}
