package model.fileStatements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.expressions.IExp;
import model.statements.IStmt;
import model.types.IType;
import model.types.IntType;
import model.types.StringType;
import model.values.IValue;
import model.values.IntValue;
import model.values.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStmt implements IStmt {
    private IExp exp;
    private String var_name;

    public ReadFileStmt(IExp e, String varN) {
        this.exp = e;
        this.var_name = varN;
    }

    @Override
    public PrgState execute(PrgState state) throws IOException {
        IDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();
        IDictionary<String, IValue> symTbl = state.getSymTable();

        StringType strType = new StringType();
        if (symTbl.containsKey(this.var_name)) {
            IValue value = symTbl.get(this.var_name);

            if (value.getType().equals(new IntType())) {
                IValue cond = this.exp.eval(symTbl, state.getHeap());

                if (cond.getType().equals(new StringType())) {
                    StringValue expValue = (StringValue) cond;

                    if (fileTable.containsKey(expValue)) {
                        BufferedReader bufferR = fileTable.get(expValue);
                        String line = bufferR.readLine();
                        if ((line != null)) {
                            symTbl.update(var_name, new IntValue(Integer.parseInt(line)));
                        } else {
                            symTbl.update(var_name, new IntValue(0));
                        }

                        return null;
                    }
                    throw new CustomException("There is no entry associated to this filename");
                }
                throw new CustomException("Given variable is not an string!");
            }
            throw new CustomException("Given variable is not an int!");
        }
        throw new CustomException("Given variable is not defined!");
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws CustomException {
        IType typeVar = typeEnv.get(this.var_name);
        IType typeExp = this.exp.typeCheck(typeEnv);

        if (typeVar.equals(new IntType()) && typeExp.equals(new StringType())) {
            return typeEnv;
        }
        else
            throw new CustomException("Invalid variable name or the expression doesn't have a String type!");
    }

    @Override
    public String toString() {
        return "readFile(" + this.exp.toString() + "," + this.var_name + ")";
    }
}
