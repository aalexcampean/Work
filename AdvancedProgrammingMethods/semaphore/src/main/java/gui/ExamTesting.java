package gui;

public class ExamTesting {
    public static void main(String[] args) {
        int size = 4;
        byte[] s = "abcd".getBytes();

        for (int i = 0; i < size; ++i) {
            byte tmp = s[i];
            s[i] = s[size - 1 - i];
            s[size - 1 - i] = tmp;
        }

        System.out.println(new String(s));
    }
}
