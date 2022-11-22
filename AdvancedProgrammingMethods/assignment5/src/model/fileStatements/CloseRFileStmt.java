package model.fileStatements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.adtContainers.IHeap;
import model.expressions.IExp;
import model.statements.IStmt;
import model.types.StringType;
import model.values.IValue;
import model.values.StringValue;

import java.io.BufferedReader;
import java.io.IOException;


public class CloseRFileStmt implements IStmt {
    private IExp exp;

    public CloseRFileStmt(IExp e){
        this.exp = e;
    }

    @Override
    public PrgState execute(PrgState state) throws IOException {
        IDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();
        IDictionary<String, IValue> symTbl = state.getSymTable();

        IValue expValue = exp.eval(symTbl, state.getHeap());

        if (expValue.getType().equals(new StringType())) {
            StringValue sValue = (StringValue) expValue;

            if (fileTable.containsKey(sValue)) {
                BufferedReader bufferR = fileTable.get(sValue);
                bufferR.close();
                fileTable.remove(sValue);
                return null;
            }
            throw new CustomException("There is no entry associated to this filename");
        }
        throw new CustomException("The type must be a string");
    }

    @Override
    public String toString() {
        return "closeFile(" + this.exp.toString() + ")";
    }
}
