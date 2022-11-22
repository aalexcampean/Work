package model.adtContainers;

public interface IStack<T> {
    void push(T v);
    T pop();
    T peek();
    boolean isEmpty();
}
