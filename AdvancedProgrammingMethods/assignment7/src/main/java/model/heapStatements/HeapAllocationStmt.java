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

public class HeapAllocationStmt implements IStmt {
    private String var_name;
    private IExp exp;

    public HeapAllocationStmt(String vn, IExp e) {
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
                IValue evalExp = this.exp.eval(symTbl, heap);
                RefValue refVal = (RefValue) value;
                if (evalExp.getType().equals(refVal.getLocationType())) {
                    int key = heap.add(evalExp);
                    RefValue newRefValue = new RefValue(key, refVal.getLocationType());
                    symTbl.update(this.var_name, newRefValue);
                    return null;
                }
                throw new CustomException("The types do not coincide!");
            }
            throw new CustomException("The variable associated to the provided VarName is not of type RefType");
        }
        throw new CustomException("The provided VarName couldn't be found in Symbol Table");
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        IType typeVar = typeEnv.get(this.var_name);
        IType typeExp = this.exp.typeCheck(typeEnv);

        if (typeVar.equals(new RefType(typeExp))) {
            return typeEnv;
        }
        else
            throw new CustomException("In the Heap Allocation the right hand side and left hand side have different types!");
    }

    @Override
    public String toString() {return "(new " + this.var_name + " " + this.exp.toString() + ")";}
}
