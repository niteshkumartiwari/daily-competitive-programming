import java.util.*;
import java.util.function.Consumer;

public class Sample {
  public static void main(String[] args) {
    List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    System.out.println(
      numbers.stream()
             .filter(e -> e % 2 == 0)
             .map(e -> e * 2.0)
             .reduce(0.0, (carry, e) -> carry + e));
           
    System.out.println(
      numbers.stream()
             .filter(e -> e % 2 == 0)
             .mapToDouble(e -> e * 2.0)
             .sum());


    //filter: 0 <= number of elements in the output <= number of input
    //parameter: Stream<T> filter takes Predicate<T>
    
    //map transforms values
    // number of output == number of input
    //no guarantee on the type of the output with respect to the type of the input
    //parameter:  Stream<T> map takes Function<T, R> to return Stream<R>
   
   
 //both filter and map stay within their swimlanes
 
 //reduce cuts across the swimlanes
 
 //reduce on Stream<T> takes two parameters:
 //first parameter is of type T
 //second parameter is of type BiFunction<R, T, R> to produce a result of R
 /*
        filter      map           reduce
                                  0.0
                                   \
 x1       |                         \
---------------------------          \
 x2       ->          x2'     ->      +
---------------------------            \
 x3       |                             \
---------------------------              \
 x4       ->          x4'      ->         +
---------------------------                \
                                            \




      1            2             3           4
      |           |              |           |
1 -> *  -> 1 ->   *  -> 2   ->   *  -> 6  -> * -> 24   


 */
  }
}