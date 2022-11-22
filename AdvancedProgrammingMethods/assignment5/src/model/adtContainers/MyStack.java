package model.adtContainers;

import exception.CustomException;
import model.statements.CompStmt;
import model.statements.IStmt;

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

    public String inOrderTraversal(IStmt stmt) {
        if (stmt instanceof CompStmt) {
            String returnString = "";

            CompStmt newStmt = (CompStmt) stmt;
            IStmt left = newStmt.getFirst();
            IStmt right = newStmt.getSecond();

            if (left instanceof CompStmt) {
                returnString += inOrderTraversal(left);
            }
            else if (left != null) {
                returnString += left.toString() + "\n";
            }

            if (right instanceof CompStmt) {
                returnString += inOrderTraversal(right);
            }
            else if (right != null) {
                returnString += right.toString() + "\n";
            }
            return returnString;
        }
        else {
            return "\n" + stmt.toString() + "\n";
        }
    }

    @Override
    public String toString() {
        StringBuilder stringRep = new StringBuilder();

        for (T elem : this.stack) {
            if (elem instanceof IStmt){
                stringRep.append(inOrderTraversal((IStmt) elem));
            }
            else {
                stringRep.append(elem.toString());
            }
        }
        return stringRep.toString();
    }
}
