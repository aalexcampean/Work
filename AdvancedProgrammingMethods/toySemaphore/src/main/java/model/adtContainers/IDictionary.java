package model.adtContainers;

import java.util.Collection;
import java.util.List;
import java.util.Map;

public interface IDictionary<T1, T2> {
    Map<T1, T2> getContent();
    void add(T1 id, T2 value);
    void update(T1 id, T2 value);
    void remove(T1 id);
    T2 get(T1 id);
    boolean containsKey(T1 id);
    int size();
    Collection<T2> values();
    IDictionary<T1, T2> deepCopy();
}
