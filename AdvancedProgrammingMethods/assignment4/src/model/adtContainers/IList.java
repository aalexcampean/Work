package model.adtContainers;

public interface IList<T> {
    void add(T v);
    T remove();
    int size();
    T get(int pos);
    boolean isEmpty();
    void clear();
}
