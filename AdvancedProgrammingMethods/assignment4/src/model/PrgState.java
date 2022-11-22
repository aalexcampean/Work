package model;

import model.adtContainers.*;
import model.statements.IStmt;
import model.values.IValue;
import model.values.StringValue;

import java.io.BufferedReader;

public class PrgState {
    private IStack<IStmt> exeStack;
    private IDictionary<String, IValue> symTable;
    private IList<IValue> out;
    private IStmt originalProgram;
    private IDictionary<StringValue, BufferedReader> fileTable;
    private IHeap<IValue> heap;

    public PrgState(IStmt stmt) {
        this.exeStack = new MyStack<IStmt>();
        this.symTable = new MyDictionary<String, IValue>();
        this.out = new MyList<IValue>();
        this.originalProgram = stmt;
        this.exeStack.push(stmt);
        this.fileTable = new MyDictionary<StringValue, BufferedReader>();
        this.heap = new MyHeap<IValue>();
    }

    public PrgState(IStack<IStmt> eStack, IDictionary<String, IValue> sTable, IList<IValue> o, IStmt orgProgram, IDictionary<StringValue, BufferedReader> fTable, IHeap<IValue> h){
        this.exeStack = eStack;
        this.symTable = sTable;
        this.out = o;
        this.originalProgram = orgProgram;
        this.exeStack.push(orgProgram);
        this.fileTable = fTable;
        this.heap = h;
    }

    public IStack<IStmt> getExeStack() {return this.exeStack;}
    public IDictionary<String, IValue> getSymTable() {return this.symTable;}
    public MyList<IValue> getOut() {return (MyList<IValue>) this.out;}
    public void setOut(MyList<IValue> output) {this.out = output;}
    public IDictionary<StringValue, BufferedReader> getFileTable() {return this.fileTable;}
    public IHeap<IValue> getHeap() {return this.heap;}

    public String toString() {
        return "------------------------------------------------------------------------------------" +
                "\n------- Execution Stack: -------\n" + this.exeStack.toString() +
                "\n------- Symbol Table: -------\n" + this.symTable.toString() +
                "\n------- Out: -------\n" + this.out.toString() +
//                "\nOriginal Program: " + this.originalProgram.toString() +
                "\n------- FileTable: -------\n" + this.fileTable.toString() +
                "\n------- Heap: -------\n" + this.heap.toString() +
                "------------------------------------------------------------------------------------\n";
    }
}
