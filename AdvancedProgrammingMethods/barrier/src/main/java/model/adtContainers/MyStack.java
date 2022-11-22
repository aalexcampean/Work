package model.adtContainers;

import exception.CustomException;
import model.statements.CompStmt;
import model.statements.IStmt;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class MyStack<T> implements IStack<T>{
    private Stack<T> stack;

    public MyStack(){
        this.stack = new Stack<T>();
    }

    @Override
    public void push(T v) {
        this.stack.push(v);
    }

    @Override
    public T pop() {
        if(this.isEmpty()){
            throw new CustomException("Empty stack!");
        }
        return this.stack.pop();
    }

    @Override
    public T peek() {
        return this.stack.peek();
    }

    @Override
    public boolean isEmpty() {
        return this.stack.isEmpty();
    }

    @Override
    public List<IStmt> getStmts() {
        List<IStmt> stmtsInStack = new ArrayList<>();
        for (T elem : this.stack) {
            if (elem instanceof IStmt) {
                inOrderTraversal((IStmt) elem, stmtsInStack);
            }
        }
        return stmtsInStack;
    }

    @Override
    public void inOrderTraversal(IStmt stmt, List<IStmt> stmtsStack) {
        if (stmt instanceof CompStmt) {

            CompStmt newStmt = (CompStmt) stmt;
            IStmt left = newStmt.getFirst();
            IStmt right = newStmt.getSecond();

            if (left instanceof CompStmt) {
                inOrderTraversal(left, stmtsStack);
            } else if (left != null) {stmtsStack.add(left);}

            if (right instanceof CompStmt) {
                inOrderTraversal(right, stmtsStack);
            } else if (right != null) {stmtsStack.add(right);}
        }
        else {
            stmtsStack.add(stmt);
        }
    }

    @Override
    public String toString() {
        StringBuilder stringRep = new StringBuilder();
        List<IStmt> stmtsInStack = getStmts();

        for (IStmt s : this.getStmts()) {
            stringRep.append(s.toString() + "\n");
        }
        return stringRep.toString();
    }
}
