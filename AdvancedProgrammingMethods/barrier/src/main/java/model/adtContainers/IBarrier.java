package model.adtContainers;

import javafx.util.Pair;

import java.util.ArrayList;

public interface IBarrier {
    IDictionary<Integer, Pair<Integer, ArrayList<Integer>>> getContent();
    void setContent(IDictionary<Integer, Pair<Integer, ArrayList<Integer>>> newContent);
    Pair<Integer, ArrayList<Integer>> get(int key);
    boolean containsKey(int key);
    Integer getFreeAddress();
    int add(Pair<Integer, ArrayList<Integer>> listPair);
    void update(Integer key, Pair<Integer, ArrayList<Integer>> listPair);
}
