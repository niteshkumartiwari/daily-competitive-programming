import java.util.*;

public class Sample {
  public static void main(String[] args) {
    List<Integer> numbers = Arrays.asList(1, 2, 3, 5, 4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20);
    
    numbers.stream() //  vv
           .filter(Sample::isGT3)
           .filter(Sample::isEven)
           .map(Sample::doubleIt);
           //.findFirst();
    System.out.println("DONE");
    //you are more efficient, not when you work faster, but when you
    //don't work at all.
    
    //lazy evaluation is possible only if the functions don't have
    //side effect (don't print stuff like I do in this example).
  }
  public static boolean isGT3(int number) {
    System.out.println("isGT3 " + number);
    return number > 3;
  }
  public static boolean isEven(int number) {
    System.out.println("isEven " + number);
    return number % 2 == 0;
  }
  public static int doubleIt(int number) {
    System.out.println("doubleIt " + number);
    return number * 2;
  }
}