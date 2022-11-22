package model.adtContainers;

import javafx.util.Pair;

import java.util.ArrayList;

public class MyBarrier implements IBarrier {
    private IDictionary<Integer, Pair<Integer, ArrayList<Integer>>> barrier;
    private Integer free_address = 1;

    public MyBarrier() {
        this.barrier = new MyDictionary<>();
    }

    @Override
    public IDictionary<Integer, Pair<Integer, ArrayList<Integer>>> getContent() {
        return this.barrier;
    }

    @Override
    public void setContent(IDictionary<Integer, Pair<Integer, ArrayList<Integer>>> newContent) {
        this.barrier = newContent;
    }

    @Override
    public Pair<Integer, ArrayList<Integer>> get(int key) {
        return this.barrier.get(key);
    }

    @Override
    public boolean containsKey(int key) {
        return this.barrier.containsKey(key);
    }

    @Override
    public Integer getFreeAddress() {
        return this.free_address;
    }

    @Override
    public int add(Pair<Integer, ArrayList<Integer>> listPair) {
        this.barrier.add(this.free_address++, listPair);
        return this.free_address - 1;
    }

    @Override
    public void update(Integer key, Pair<Integer, ArrayList<Integer>> listPair) {
        this.barrier.update(key, listPair);
    }

    @Override
    public String toString() {
        return this.barrier.toString();
    }
}
