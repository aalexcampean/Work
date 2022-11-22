package model.adtContainers;

public class MyTriplet<T1, T2, T3> implements ITriplet {

    private T1 value0;
    private T2 value1;
    private T3 value2;

    public MyTriplet(T1 val0, T2 val1, T3 val2){
        this.value0 = val0;
        this.value1 = val1;
        this.value2 = val2;
    }

    @Override
    public T1 getValue0() {
        return value0;
    }

    @Override
    public T2 getValue1() {
        return value1;
    }

    @Override
    public T3 getValue2() {
        return value2;
    }
}
