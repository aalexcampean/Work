package model.adtContainers;

import model.statements.IStmt;

import java.util.List;

public interface IStack<T> {
    void push(T v);
    T pop();
    T peek();
    boolean isEmpty();
    List<IStmt> getStmts();
    void inOrderTraversal(IStmt stmt, List<IStmt> stmtsStack);
}
