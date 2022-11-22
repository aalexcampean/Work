package model;

import exception.CustomException;
import model.adtContainers.*;
import model.statements.IStmt;
import model.values.IValue;
import model.values.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class PrgState {
    private static int threadCount = 0;
    private final int threadId;
    private IStack<IStmt> exeStack;
    private IDictionary<String, IValue> symTable;
    private IList<IValue> out;
    private IStmt originalProgram;
    private IDictionary<StringValue, BufferedReader> fileTable;
    private IHeap<IValue> heap;

    private synchronized static int getThreadId() {
        threadCount ++;
        return threadCount - 1;
    }

    public PrgState(IStmt stmt) {
        threadId = getThreadId();
        this.exeStack = new MyStack<IStmt>();
        this.exeStack.push(stmt);

        this.symTable = new MyDictionary<String, IValue>();
        this.out = new MyList<IValue>();
        this.originalProgram = stmt;
        this.fileTable = new MyDictionary<StringValue, BufferedReader>();
        this.heap = new MyHeap<IValue>();
    }

    public PrgState(IStack<IStmt> eStack, IDictionary<String, IValue> sTable, IList<IValue> o, IStmt orgProgram, IDictionary<StringValue, BufferedReader> fTable, IHeap<IValue> h){
        threadId = getThreadId();
        this.exeStack = eStack;
        this.exeStack.push(orgProgram);

        this.symTable = sTable;
        this.out = o;
        this.originalProgram = orgProgram;
        this.fileTable = fTable;
        this.heap = h;
    }

    public int getId() {return this.threadId;}

    public IStack<IStmt> getExeStack() {return this.exeStack;}
    public IDictionary<String, IValue> getSymTable() {return this.symTable;}
    public MyList<IValue> getOut() {return (MyList<IValue>) this.out;}
    public void setOut(IList<IValue> output) {this.out = output;}
    public IDictionary<StringValue, BufferedReader> getFileTable() {return this.fileTable;}
    public IHeap<IValue> getHeap() {return this.heap;}

    public Boolean isNotCompleted() {
        return !this.exeStack.isEmpty();
    }

    public PrgState oneStep() throws IOException {
        if (this.exeStack.isEmpty()){throw new CustomException("Program state stack is empty!");}

        IStmt currentStmt = this.exeStack.pop();
        return currentStmt.execute(this);
    }

    public String toString() {
        return "\n------------------------------------------------------------------------------------" +
                "\n------- Id: " + threadId + " -------\n" +
                "\n------- Execution Stack: -------\n" + this.exeStack.toString() +
                "\n------- Symbol Table: -------\n" + this.symTable.toString() +
                "\n------- Out: -------\n" + this.out.toString() +
//                "\nOriginal Program: " + this.originalProgram.toString() +
                "\n------- FileTable: -------\n" + this.fileTable.toString() +
                "\n------- Heap: -------\n" + this.heap.toString();
    }
}
