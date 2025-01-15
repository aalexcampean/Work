package Model;

public final class Task implements Runnable {
    private final int start;
    private final int end;
    private final Polynomial polynomial1;
    private final Polynomial polynomial2;
    private final Polynomial resultPolynomial;

    public Task(int start, int end, Polynomial polynomial1, Polynomial polynomial2, Polynomial resultPolynomial) {
        this.start = start;
        this.end = end;
        this.polynomial1 = polynomial1;
        this.polynomial2 = polynomial2;
        this.resultPolynomial = resultPolynomial;
    }

    @Override
    public void run() {
        for (int index = start; index < end; index++) {
            //case - no more elements to calculate
            if (index > resultPolynomial.getCoefficients().size()) {
                return;
            }
            //find all the pairs that we add to obtain the value of a result coefficient
            for (int j = 0; j <= index; j++) {
                if (j < polynomial1.getCoefficients().size() && (index - j) < polynomial2.getCoefficients().size()) {
                    int value = polynomial1.getCoefficients().get(j) * polynomial2.getCoefficients().get(index - j);
                    resultPolynomial.getCoefficients().set(index, resultPolynomial.getCoefficients().get(index) + value);
                }
            }
        }
    }
}