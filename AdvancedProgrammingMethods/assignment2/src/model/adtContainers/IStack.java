package model.adtContainers;

public interface IStack<T> {
    void push(T v);
    T pop() throws Exception;
    T peek();
    boolean isEmpty();
}
