package model.adtContainers;

import javafx.util.Pair;

import java.util.ArrayList;

public class MyLatch implements ILatch {
    private IDictionary<Integer, Integer> latch;
    private Integer free_address = 1;

    public MyLatch() {
        this.latch = new MyDictionary<>();
    }

    @Override
    public IDictionary<Integer, Integer> getContent() {
        return this.latch;
    }

    @Override
    public void setContent(IDictionary<Integer, Integer> newContent) {
        this.latch = newContent;
    }

    @Override
    public Integer get(int key) {
        return this.latch.get(key);
    }

    @Override
    public boolean containsKey(int key) {
        return this.latch.containsKey(key);
    }

    @Override
    public Integer getFreeAddress() {
        return this.free_address;
    }

    @Override
    public int add(Integer value) {
        this.latch.add(this.free_address++, value);
        return this.free_address - 1;
    }

    @Override
    public void update(Integer key, Integer value) {
        this.latch.update(key, value);
    }

    @Override
    public String toString() {
        return this.latch.toString();
    }
}
