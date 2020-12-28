import java.util.*;

public class Sample {
  public static void main(String[] args) {
//function has 4 things
//1. name - anonymous
      //2. parameter list
      //3. body
//4. return type - inferred


    Thread th = new Thread(() -> System.out.println("In another thread"));
    th.start();
    
    System.out.println("In main");
  }
}