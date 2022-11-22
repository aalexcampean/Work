package model.fileStatements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.expressions.IExp;
import model.statements.IStmt;
import model.values.IValue;
import model.values.StringValue;

import java.io.BufferedReader;


public class CloseRFileStmt implements IStmt {
    private IExp exp;

    public CloseRFileStmt(IExp e){
        this.exp = e;
    }

    @Override
    public PrgState execute(PrgState state) {
        IDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();
        IDictionary<String, IValue> symTbl = state.getSymTable();

        try{
            StringValue sValue = (StringValue) this.exp.eval(symTbl, state.getHeap());

            if (fileTable.containsKey(sValue)) {
                BufferedReader bufferR = fileTable.get(sValue);
                bufferR.close();
                fileTable.remove(sValue);
            }
            else {
                throw new CustomException("There is no entry associated to this filename");
            }

        }
        catch (Exception e){ System.out.println(e.getMessage());}
        return state;
    }

    @Override
    public String toString() {
        return "closeFile(" + this.exp.toString() + ")";
    }
}
