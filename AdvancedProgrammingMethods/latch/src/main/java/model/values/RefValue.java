package model.values;

import model.types.IType;
import model.types.RefType;

public class RefValue implements IValue{
    private int address;
    private IType locationType;

//    public RefValue() {
//        this.address = 0;
//        this.locationType = null;
//    }

    public RefValue(int given_address, IType given_location_type) {
        this.address = given_address;
        this.locationType = given_location_type;
    }

//    @Override
//    public boolean equals(Object o) {
//        if (o == null || o.getClass() != this.getClass()){
//            return false;
//        }
//        RefValue oValue = (RefValue) o;
//        return this.address == oValue.getAddress();
//    }

    public int getAddress() {
        return this.address;
    }
    public IType getLocationType() {return this.locationType;}
    public void setAddress(int a) { this.address = a; }

    @Override
    public IType getType() {
        return new RefType(this.locationType);
    }

    @Override
    public IValue deepCopy() {
        return new RefValue(this.address, this.locationType);
    }

    @Override
    public String toString() {
        return '(' + Integer.toString(this.address) + ", " + this.locationType.toString() + ')';
    }
}
