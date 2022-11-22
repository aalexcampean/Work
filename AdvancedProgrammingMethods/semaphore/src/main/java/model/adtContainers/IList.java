package model.adtContainers;

import java.util.List;

public interface IList<T> {
    void add(T v);
    T remove();
    int size();
    T get(int pos);
    List<T> getAll();
    boolean isEmpty();
    void clear();
}
