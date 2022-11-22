package model.adtContainers;

import exception.CustomException;

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
    public T pop() throws Exception{
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
    public String toString(){
        return this.stack.toString();
    }
}
