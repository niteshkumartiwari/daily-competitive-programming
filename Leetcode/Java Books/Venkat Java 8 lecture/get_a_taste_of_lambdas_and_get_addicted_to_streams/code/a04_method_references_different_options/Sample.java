import java.util.*;
import java.util.function.Consumer;

public class Sample {
  public static void main(String[] args) {
    List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        
    // numbers.forEach(e -> System.out.println(e));
    // numbers.forEach(System.out::println);
    
    // numbers.stream()
    //        // .map(e -> String.valueOf(e))
    //        .map(String::valueOf)
    //        .forEach(System.out::println);
    
    // numbers.stream()
    //        .map(e -> String.valueOf(e))
    //        // .map(e -> e.toString())
    //        .map(String::toString)
    //        .forEach(System.out::println);

    // System.out.println(
    //   numbers.stream()
    //          // .reduce(0, (total, e) -> Integer.sum(total, e)));
    //          .reduce(0, Integer::sum));
    
    System.out.println(
      numbers.stream()
             .map(String::valueOf)
             // .reduce("", (carry, str) -> carry.concat(str)));
             .reduce("", String::concat));
  }
}