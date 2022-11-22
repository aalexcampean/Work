package model.adtContainers;

public class MyLock implements ILock {
    private IDictionary<Integer, Integer> lock;
    private Integer free_address = 1;

    public MyLock() {
        this.lock = new MyDictionary<>();
    }

    @Override
    public IDictionary<Integer, Integer> getContent() {
        return this.lock;
    }

    @Override
    public void setContent(IDictionary<Integer, Integer> newContent) {
        this.lock = newContent;
    }

    @Override
    public Integer get(int key) {
        return this.lock.get(key);
    }

    @Override
    public boolean containsKey(int key) {
        return this.lock.containsKey(key);
    }

    @Override
    public Integer getFreeAddress() {
        return this.free_address;
    }

    @Override
    public int add(Integer value) {
        this.lock.add(this.free_address++, value);
        return this.free_address - 1;
    }

    @Override
    public void update(Integer key, Integer value) {
        this.lock.update(key, value);
    }

    @Override
    public String toString() {
        return this.lock.toString();
    }
}
