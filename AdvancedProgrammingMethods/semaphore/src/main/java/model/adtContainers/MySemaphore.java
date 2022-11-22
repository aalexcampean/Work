package model.adtContainers;

import javafx.util.Pair;

import java.util.ArrayList;

public class MySemaphore implements ISemaphore {
    private IDictionary<Integer, Pair<Integer, ArrayList<Integer>>> semaphore;
    private Integer free_address = 1;

    public MySemaphore() {
        this.semaphore = new MyDictionary<>();
    }

    @Override
    public IDictionary<Integer, Pair<Integer, ArrayList<Integer>>> getContent() {
        return this.semaphore;
    }

    @Override
    public void setContent(IDictionary<Integer, Pair<Integer, ArrayList<Integer>>> newContent) {
        this.semaphore = newContent;
    }

    @Override
    public Pair<Integer, ArrayList<Integer>> get(int key) {
        return this.semaphore.get(key);
    }

    @Override
    public boolean containsKey(int key) {
        return this.semaphore.containsKey(key);
    }

    @Override
    public Integer getFreeAddress() {
        return this.free_address;
    }

    @Override
    public int add(Pair<Integer, ArrayList<Integer>> listPair) {
        this.semaphore.add(this.free_address++, listPair);
        return this.free_address - 1;
    }

    @Override
    public void update(Integer key, Pair<Integer, ArrayList<Integer>> listPair) {
        this.semaphore.update(key, listPair);
    }

    @Override
    public String toString() {
        return this.semaphore.toString();
    }
}
