package model.adtContainers;

import exception.CustomException;
import model.values.IValue;
import model.values.RefValue;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

public class MyHeap<T2> implements IHeap<T2>{
    private Map<Integer, T2> heap;
    private int free_address;

    public MyHeap() {
        this.heap = new HashMap<Integer, T2>();
        this.free_address = 1;
    }

    public MyHeap(HashMap<Integer, T2> h, int f) {
        this.heap = h;
        this.free_address = f;
    }

    @Override
    public int add(T2 value) {
        if (this.heap.containsKey(this.free_address)) {
            throw new CustomException("Key already exists!");
        }
        this.heap.put(this.free_address++, value);
        return this.free_address - 1;
    }

    @Override
    public void update(int key, T2 value) {
        if (!this.heap.containsKey(key)) {
            throw new CustomException("Key doesn't exist!");
        }
        this.heap.put(key, value);
    }

    @Override
    public void remove(int key) {
        if (!this.heap.containsKey(key)) {
            throw new CustomException("Key doesn't exist!");
        }
        this.heap.remove(key);
    }

    @Override
    public T2 get(int key) {
        return this.heap.get(key);
    }

    @Override
    public boolean containsKey(int key) {
        return this.heap.containsKey(key);
    }

    @Override
    public int size() {
        return this.heap.size();
    }

    @Override
    public Collection<T2> values() {
        return this.heap.values();
    }

    @Override
    public void setContent(Map<Integer, T2> newContent) {
        this.heap = newContent;
    }

    @Override
    public Map<Integer, T2> getContent() {
        return this.heap;
    }

    @Override
    public String toString() {
        StringBuilder stringRep = new StringBuilder();
        this.heap.forEach((k, v) -> stringRep.append(k).append(" = ").append(v.toString()).append("\n"));
        return stringRep.toString();
    }

//    @Override
//    public IHeap<T2> deepCopy() {
//        IHeap<T2> copyHeap = new MyHeap<T2>();
//        for(int key : this.heap.keySet()){
//            copyHeap.add(key, this.heap.get(key));
//        }
//        return copyHeap;
//    }
}
