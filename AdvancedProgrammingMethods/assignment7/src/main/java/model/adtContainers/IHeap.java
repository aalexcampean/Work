package model.adtContainers;

import java.util.Collection;
import java.util.Map;

public interface IHeap<T2> {
    Map<Integer, T2> getContent();
    void setContent(Map<Integer, T2> newContent);
    T2 get(int key);
    boolean containsKey(int key);
    int size();
    Collection<T2> values();
    int add(T2 value);
    void update(int key, T2 value);
    void remove(int key);
//    IHeap<T2> deepCopy();
}
