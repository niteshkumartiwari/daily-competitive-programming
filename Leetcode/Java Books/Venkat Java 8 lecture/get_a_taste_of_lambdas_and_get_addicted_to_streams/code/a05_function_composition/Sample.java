import java.util.*;
import java.util.function.Consumer;

public class Sample {
  public static void main(String[] args) {
    List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    //given the values, double the even numbers and total.
    
    int result = 0;
    
    for(int e : numbers) {
      if(e % 2 == 0) {
        result += e * 2;
      }
    }
    
    System.out.println(result);
    
    System.out.println(
      numbers.stream()
             .filter(e -> e % 2 == 0)
             .mapToInt(e -> e * 2)
             .sum());
  }
}