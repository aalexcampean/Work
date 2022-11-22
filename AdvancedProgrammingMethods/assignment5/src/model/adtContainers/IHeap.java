package model.adtContainers;

import java.util.Collection;
import java.util.Map;

public interface IHeap<T2> {
    int add(T2 value);
    void update(int key, T2 value);
    void remove(int key);
    T2 get(int key);
    boolean containsKey(int key);
    int size();
    Collection<T2> values();
    void setContent(Map<Integer, T2> newContent);
    Map<Integer, T2> getContent();
//    IHeap<T2> deepCopy();
}
