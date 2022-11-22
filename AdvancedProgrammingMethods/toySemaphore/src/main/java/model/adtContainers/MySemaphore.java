package model.adtContainers;

import javafx.util.Pair;

import java.util.ArrayList;

public class MySemaphore implements ISemaphore {
    private IDictionary<Integer, MyTriplet<Integer, ArrayList<Integer>, Integer>> semaphore;
    private Integer free_address = 1;

    public MySemaphore() {
        this.semaphore = new MyDictionary<>();
    }

    @Override
    public IDictionary<Integer, MyTriplet<Integer, ArrayList<Integer>, Integer>> getContent() {
        return this.semaphore;
    }

    @Override
    public void setContent(IDictionary<Integer, MyTriplet<Integer, ArrayList<Integer>, Integer>> newContent) {
        this.semaphore = newContent;
    }

    @Override
    public MyTriplet<Integer, ArrayList<Integer>, Integer> get(int key) {
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
    public int add(MyTriplet<Integer, ArrayList<Integer>, Integer> listTriplet) {
        this.semaphore.add(this.free_address++, listTriplet);
        return this.free_address - 1;
    }

    @Override
    public void update(Integer key, MyTriplet<Integer, ArrayList<Integer>, Integer> listTriplet) {
        this.semaphore.update(key, listTriplet);
    }

    @Override
    public String toString() {
        return this.semaphore.toString();
    }
}
