package model.fileStatements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.expressions.IExp;
import model.statements.IStmt;
import model.types.StringType;
import model.values.IValue;
import model.values.StringValue;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class OpenRFileStmt implements IStmt {
    private IExp exp;

    public OpenRFileStmt(IExp e) {
        this.exp = e;
    }

    @Override
    public PrgState execute(PrgState state) {
        IDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();
        IDictionary<String, IValue> symTbl = state.getSymTable();

        IValue expValue = this.exp.eval(symTbl, state.getHeap());

        if (expValue.getType().equals(new StringType())){
            StringValue stringExpValue = (StringValue) expValue;
            if (!fileTable.containsKey(stringExpValue)){
                try{
                    BufferedReader bufferR = new BufferedReader(new FileReader(stringExpValue.getValue()));
                    fileTable.add(stringExpValue, bufferR);
                }
                catch (IOException e){
                    System.out.println(e.getMessage());
                }
                return null;
            }
            throw new CustomException("The given file already exists!");
        }
        throw new CustomException("The expression doesn't have the StringType!");
    }

    @Override
    public String toString() {return "openRFile(" + this.exp.toString() + ")";}
}
