package model.adtContainers;

import exception.CustomException;

import java.util.List;

public interface IDictionary<T1, T2> {
    void add(T1 id, T2 value);
    void update(T1 id, T2 value);
    void remove(T1 id);
    T2 get(T1 id);
    boolean containsKey(T1 id);
    int size();
    List<T2> values();
    IDictionary<T1, T2> deepCopy();
}
