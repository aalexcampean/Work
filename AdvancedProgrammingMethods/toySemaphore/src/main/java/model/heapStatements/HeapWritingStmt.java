package model.heapStatements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.expressions.IExp;
import model.statements.IStmt;
import model.types.IType;
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

                        return null;
                    }
                    throw new CustomException("Types do not coincide!");
                }
                throw new CustomException("The Heap does not contain that key!");
            }
            throw new CustomException("The variable associated to the provided VarName is not of type RefType");
        }
        throw new CustomException("VarName not found in SymbolTable!");
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        IType typeVar = typeEnv.get(this.var_name);
        IType typeExp = this.exp.typeCheck(typeEnv);

        if (typeVar.equals(new RefType(typeExp))) {
            return typeEnv;
        }
        else
            throw new CustomException("In the Heap Writing the right hand side and left hand side have different types!");
    }

    @Override
    public String toString() {return "wH(" + this.var_name + " " + this.exp.toString() + ")";}
}
