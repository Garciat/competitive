import java.util.Scanner;
import java.math.BigInteger;

public class catalan
{
    static BigInteger product(int xo, int dx, int mx)
    {
        BigInteger p = BigInteger.ONE;
        for (int x = xo; x <= mx; x += dx)
            p = p.multiply(BigInteger.valueOf(x));
        return p;
    }
    
    static BigInteger catalan(int n)
    {
        int c = n / 2;
        int d = n % 2;
        int m = n - c;
        
        int g = 0;
        for (int i = m; (i /= 2) > 0; )
            g += i;
        
        BigInteger k = BigInteger.valueOf(1 << (c - g));
        BigInteger top = product(n - d + 3, 2, n * 2).multiply(k);
        
        BigInteger[] odds = new BigInteger[(m + 1) / 2];
        int t = 3;
        for (int i = 0; i < odds.length; ++i, t += 2)
            odds[i] = BigInteger.valueOf(t);
        
        BigInteger bot = BigInteger.ONE;
        for (int i = m; i > 0; i /= 2)
        {
            BigInteger p = BigInteger.ONE;
            int z = 3;
            for (int x = 0; x < odds.length && z <= i; ++x, z += 2)
                p = p.multiply(odds[x]);
            bot = bot.multiply(p);
        }
        
        return top.divide(bot);
    }
    
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        
        BigInteger c = catalan(n + 1);
        
        System.out.println(c);
    }
}
