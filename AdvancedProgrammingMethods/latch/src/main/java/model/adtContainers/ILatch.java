package model.adtContainers;

public interface ILatch {
    IDictionary<Integer, Integer> getContent();
    void setContent(IDictionary<Integer, Integer> newContent);
    Integer get(int key);
    boolean containsKey(int key);
    Integer getFreeAddress();
    int add(Integer value);
    void update(Integer key, Integer value);
}
