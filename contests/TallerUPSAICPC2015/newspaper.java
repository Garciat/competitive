// https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2315
import java.util.*;
import java.io.*;

public class Main {
  private static final BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
  
  private static int readInt() throws Exception {
    return Integer.parseInt(in.readLine());
  }
  
  public static void main(String[] args) throws Exception {
    int n = readInt();
    
    for (int t = 0; t < n; ++t) {
      int[] weights = new int[1000];
      
      int k = readInt();
      
      for (int i = 0; i < k; ++i) {
        int c = in.read();
        in.read(); // skip space
        weights[c] = readInt();
      }
      
      int m = readInt();
      int value = 0;
      int lines = 0;
      
      for (;;) {
        int c = in.read();
        value += weights[c];
        if ((char)c == '\n') lines += 1;
        if (lines == m) break;
      }
      
      System.out.printf("%d.%02d$\n", value/100, value%100);
    }
  }
}