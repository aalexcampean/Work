package model.adtContainers;

import exception.CustomException;

public interface IDictionary<T1, T2> {
    void add(T1 id, T2 value) throws CustomException, Exception;
    void update(T1 id, T2 value) throws CustomException, Exception;
    void remove(T1 id) throws Exception;
    T2 get(T1 id);
    boolean containsKey(T1 id);
    int size();
    IDictionary<T1, T2> deepCopy() throws Exception;
}
