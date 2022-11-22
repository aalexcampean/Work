package model.fileStatements;

import exception.CustomException;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.expressions.Exp;
import model.statements.IStmt;
import model.types.IntType;
import model.types.StringType;
import model.values.IValue;
import model.values.IntValue;
import model.values.StringValue;

import java.io.BufferedReader;
import java.io.FileReader;

public class ReadFileStmt implements IStmt {
    private Exp exp;
    private String var_name;

    public ReadFileStmt(Exp e, String varN) {
        this.exp = e;
        this.var_name = varN;
    }

    @Override
    public PrgState execute(PrgState state) {
        IDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();
        IDictionary<String, IValue> symTbl = state.getSymTable();

        IntType intType = new IntType();
        StringType strType = new StringType();
        if (symTbl.containsKey(this.var_name) && symTbl.get(this.var_name).getType().getClass().equals(intType.getClass())) {
            try{
                StringValue expValue = (StringValue) this.exp.eval(symTbl);
                if (fileTable.containsKey(expValue)) {
                    BufferedReader bufferR = fileTable.get(expValue);

                    String line;
                    IntValue newIntV;
                    if ((line = bufferR.readLine()) != null){
                        newIntV = new IntValue(Integer.parseInt(line));
                    }
                    else {
                        newIntV = new IntValue(0);
                    }
                    symTbl.update(this.var_name, newIntV);
                }
                else throw new CustomException("There is no entry associated to this filename");
            }
            catch (Exception e){ System.out.println(e.getMessage());}
        }
        else throw new CustomException("Given variable is not an int!");
        return state;
    }

    @Override
    public String toString() {
        return "readFile(" + this.exp.toString() + "," + this.var_name + ")";
    }
}
