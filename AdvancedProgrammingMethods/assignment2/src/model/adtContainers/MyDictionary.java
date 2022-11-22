package model.adtContainers;

import exception.CustomException;

import java.util.HashMap;
import java.util.Map;

public class MyDictionary<T1, T2> implements IDictionary<T1, T2>{
    private Map<T1, T2> dictionary;

    public MyDictionary() {
        this.dictionary = new HashMap<T1, T2>();
    }

    @Override
    public void add(T1 id, T2 value) throws Exception {
        if (this.dictionary.containsKey(id)){
            throw new CustomException("Id already exist!");
        }
        this.dictionary.put(id, value);
    }

    @Override
    public void update(T1 id, T2 value) throws Exception {
        if (!this.dictionary.containsKey(id)){
            throw new CustomException("Id doesn't exist!");
        }
        this.dictionary.put(id, value);
    }

    @Override
    public void remove(T1 id) throws Exception{
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
    public IDictionary<T1, T2> deepCopy() throws Exception {
        IDictionary<T1, T2> copyDict = new MyDictionary<T1, T2>();
        for(T1 id : this.dictionary.keySet()){
            copyDict.add(id, this.dictionary.get(id));
        }
        return copyDict;
    }

    @Override
    public String toString(){
        return this.dictionary.toString();
    }
}
