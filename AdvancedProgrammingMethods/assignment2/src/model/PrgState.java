package model;

import model.adtContainers.*;
import model.statements.IStmt;
import model.values.IValue;

public class PrgState {
    private IStack<IStmt> exeStack;
    private IDictionary<String, IValue> symTable;
    private IList<IValue> out;
    private IStmt originalProgram;

    public PrgState(IStmt stmt) {
        this.exeStack = new MyStack<IStmt>();
        this.symTable = new MyDictionary<String, IValue>();
        this.out = new MyList<IValue>();
        this.originalProgram = stmt;
        this.exeStack.push(stmt);
    }

    public PrgState(IStack<IStmt> eStack, IDictionary<String, IValue> sTable, IList<IValue> o, IStmt orgProgram){
        this.exeStack = eStack;
        this.symTable = sTable;
        this.out = o;
        this.originalProgram = orgProgram;
        this.exeStack.push(orgProgram);
    }

    public IStack<IStmt> getExeStack() {return this.exeStack;}
    public IDictionary<String, IValue> getSymTable() {return this.symTable;}
    public MyList<IValue> getOut() {return new MyList<>();}
    public void setOut(MyList<IValue> output) {this.out = output;}

    public String toString() {
        return "-------" +
                "\nExecution Stack: " + this.exeStack.toString() +
                "\nSymbol Table: " + this.symTable.toString() +
                "\nOut: " + this.out.toString() +
                "\nOriginal Program: " + this.originalProgram.toString() + "\n";
    }
}
