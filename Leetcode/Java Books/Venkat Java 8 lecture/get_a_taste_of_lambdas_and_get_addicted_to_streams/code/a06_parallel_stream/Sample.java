import java.util.*;
import java.util.function.Consumer;

public class Sample {
  public static void main(String[] args) {
    List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    Timeit.code(() -> 
    System.out.println(
      //numbers.stream()
      numbers.parallelStream()
             .filter(e -> e % 2 == 0)
             .mapToInt(Sample::compute)
             .sum()));
  }
  public static int compute(int number) {
    //assume this is time intensive
    try { Thread.sleep(1000); } catch(Exception ex) {}
    return number * 2;
  }
}