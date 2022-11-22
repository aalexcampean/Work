package model.adtContainers;

import exception.CustomException;

import java.io.BufferedReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MyDictionary<T1, T2> implements IDictionary<T1, T2>{
    private Map<T1, T2> dictionary;

    public MyDictionary() {
        this.dictionary = new HashMap<T1, T2>();
    }

    @Override
    public void add(T1 id, T2 value) {
        if (this.dictionary.containsKey(id)){
            throw new CustomException("Id already exist!");
        }
        this.dictionary.put(id, value);
    }

    @Override
    public void update(T1 id, T2 value) {
        if (!this.dictionary.containsKey(id)){
            throw new CustomException("Id doesn't exist!");
        }
        this.dictionary.put(id, value);
    }

    @Override
    public void remove(T1 id) {
        if (!this.dictionary.containsKey(id)){
            throw new CustomException("Id doesn't exist!");
        }
        this.dictionary.remove(id);
    }

    @Override
    public T2 get(T1 id){
        return this.dictionary.get(id);
    }

    @Override
    public boolean containsKey(T1 id){
        return this.dictionary.containsKey(id);
    }

    @Override
    public int size() {
        return this.dictionary.size();
    }

    @Override
    public List<T2> values() {
        List<T2> values = new ArrayList<>();
        for(T1 id : this.dictionary.keySet()){
            values.add(this.dictionary.get(id));
        }
        return values;
    }

    @Override
    public IDictionary<T1, T2> deepCopy() {
        IDictionary<T1, T2> copyDict = new MyDictionary<T1, T2>();
        for(T1 id : this.dictionary.keySet()){
            copyDict.add(id, this.dictionary.get(id));
        }
        return copyDict;
    }

    @Override
    public String toString(){
        StringBuilder stringRep = new StringBuilder();
        this.dictionary.forEach((k, v) -> stringRep.append(k).append(" = ").append(v.toString()).append("\n"));
        return stringRep.toString();    }
}
