package Algorithms.Sequential;

import Model.Polynomial;
import Utilities.PolynomialOperations;

public class KaratsubaSequential {
    public static Polynomial multiply(Polynomial p1, Polynomial p2) throws InterruptedException {
        if (p1.getDegree() < 2 || p2.getDegree() < 2) {
            return ClassicSequential.multiply(p1,p2);
        }

        int len = Math.max(p1.getDegree(), p2.getDegree()) / 2;
        Polynomial lowP1 = new Polynomial(p1.getCoefficients().subList(0, len));
        Polynomial highP1 = new Polynomial(p1.getCoefficients().subList(len, p1.getCoefficients().size()));
        Polynomial lowP2 = new Polynomial(p2.getCoefficients().subList(0, len));
        Polynomial highP2 = new Polynomial(p2.getCoefficients().subList(len, p2.getCoefficients().size()));

        Polynomial z1 = multiply(lowP1, lowP2);
        Polynomial z2 = multiply(PolynomialOperations.add(lowP1, highP1), PolynomialOperations.add(lowP2, highP2));
        Polynomial z3 = multiply(highP1, highP2);

        //calculate the final result
        Polynomial r1 = PolynomialOperations.addZeros(z3, 2 * len);
        Polynomial r2 = PolynomialOperations.addZeros(PolynomialOperations.subtract(PolynomialOperations.subtract(z2, z3), z1), len);
        Polynomial result = PolynomialOperations.add(PolynomialOperations.add(r1, r2), z1);
        return result;
    }
}
