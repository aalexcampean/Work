import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class practice {
    public static void main(String[] args) {
        // example 1
        List<Integer> numbers1 = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);

        String finalResult1 = numbers1.stream()
                .filter(n -> {return n % 2 == 0 || n % 3 == 0;})
                .map(n -> {return "A" + Integer.toString(n + 1) + "B";})
                .reduce("", (a, b) -> a + " " + b);;
        System.out.println("result1: " + finalResult1);

        // example 2
        List<Integer> numbers2 = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

        Integer finalResult2 = numbers2.stream()
                .filter(n -> {return n % 4 == 0;})
                .map(n -> {return n + 1;})
                .reduce(0, (a, b) -> (a + b) % 2);
        System.out.println("result2: " + finalResult2);

        // example 3
        List<Integer> numbers3 = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);

        String finalResult3 = numbers3.stream()
                .filter(n -> {return n % 5 == 0 || n % 2 == 0;})
                .map(n -> {return "N" + n.toString() + "R";})
                .reduce("", (a, b) -> a + " " + b);
        System.out.println("result3: " + finalResult3);

        // example 4
        List<Integer> numbers4 = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);

        String finalResult4 = numbers4.stream()
                .filter(n -> {return n % 3 == 0 || n % 2 == 0;})
                .map(n -> {return "A" + Integer.toString(n + 1) + "B";})
                .reduce("", (a, b) -> a + " " + b);
        System.out.println("result4: " + finalResult4);

        // example 5
        List<Integer> numbers5 = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

        Integer finalResult5 = numbers5.stream()
                .filter(n -> {return n % 4 == 0;})
                .map(n -> {return n + 1;})
                .reduce(0, (a, b) -> (a + b) % 2);
        System.out.println("result5: " + finalResult5);

        // example 6
        List<Integer> numbers6 = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);

        String finalResult6 = numbers6.stream()
                .filter(n -> {return n % 2 == 0 || n % 5 == 0;})
                .map(n -> {return "N" + n.toString() + "R";})
                .reduce("", (a, b) -> a + " " + b);
        System.out.println("result6: " + finalResult6);

        // example 7
        List<Integer> numbers7 = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);

        Integer finalResult7 = numbers7.stream()
                .filter(n -> {return n % 3 == 0 || n % 7 ==0;})
                .map(n -> {return n - 1;})
                .reduce(0, (a, b) -> (a + b) % 5);
        System.out.println("result7: " + finalResult7);

        // example 8
        List<Integer> numbers8 = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

        Integer finalResult8 = numbers8.stream()
                .filter(n -> {return n % 4 == 0;})
                .map(n -> {return n + 1;})
                .reduce(0, (a, b) -> (a + b) % 2);
        System.out.println("result8: " + finalResult8);

        // example 9
        List<Integer> numbers9 = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

        List<Integer> finalResult9 = numbers9.stream()
                .filter(n -> {return n % 4 == 0;})
                .toList();
        System.out.println("result9: " + finalResult9);
    }
}
