package model.adtContainers;

import javafx.util.Pair;

import java.util.ArrayList;

public interface ISemaphore {
    IDictionary<Integer, MyTriplet<Integer, ArrayList<Integer>, Integer>> getContent();
    void setContent(IDictionary<Integer, MyTriplet<Integer, ArrayList<Integer>, Integer>> newContent);
    MyTriplet<Integer, ArrayList<Integer>, Integer> get(int key);
    boolean containsKey(int key);
    Integer getFreeAddress();
    int add(MyTriplet<Integer, ArrayList<Integer>, Integer> listPair);
    void update(Integer key, MyTriplet<Integer, ArrayList<Integer>, Integer> listPair);
}
