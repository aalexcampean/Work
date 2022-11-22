package model.adtContainers;

import exception.CustomException;
import java.util.ArrayList;
import java.util.List;

public class MyList<T> implements IList<T> {
    private List<T> list;

    public MyList(){
        this.list = new ArrayList<T>();
    }

    @Override
    public void add(T v) {
        list.add(v);
    }

    @Override
    public T remove() throws Exception{
        if(this.list.isEmpty()){
            throw new CustomException("Empty list!");
        }
        return list.remove(this.list.size() - 1);
    }

    @Override
    public int size(){
        return this.list.size();
    }

    @Override
    public T get(int pos){
        return this.list.get(pos);
    }

    @Override
    public boolean isEmpty() {
        return this.list.isEmpty();
    }

    @Override
    public void clear() {
        this.list.clear();
    }

    @Override
    public String toString(){
        return this.list.toString();
    }
}
