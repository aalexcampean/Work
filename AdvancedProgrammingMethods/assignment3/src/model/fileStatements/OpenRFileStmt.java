package model.fileStatements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.expressions.Exp;
import model.statements.IStmt;
import model.types.StringType;
import model.values.IValue;
import model.values.StringValue;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class OpenRFileStmt implements IStmt {
    private Exp exp;

    public OpenRFileStmt(Exp e) {
        this.exp = e;
    }

    @Override
    public PrgState execute(PrgState state) {
        IDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();
        IDictionary<String, IValue> symTbl = state.getSymTable();

        IValue expValue = this.exp.eval(symTbl);
        StringValue stringExpValue = (StringValue) expValue;

        StringType strType = new StringType();
        if (expValue.getType().getClass().equals(strType.getClass())){
            if (!fileTable.containsKey(stringExpValue)){
                try{
                    FileReader fileR = new FileReader(stringExpValue.toString());
                    BufferedReader bufferR = new BufferedReader(fileR);
                    fileTable.add(stringExpValue, bufferR);
                }
                catch (IOException e){
                    System.out.println(e.getMessage());
                }
            }
            else {
                throw new CustomException("The given file already exists!");
            }
        }
        else {
            throw new CustomException("The expression doesn't have the StringType!");
        }
        return state;
    }

    @Override
    public String toString() {return "openRFile(" + this.exp.toString() + ")";}
}
