using System;
using System.Numerics;

public static class Program
{
    static BigInteger Product(Int32 x, Int32 dx, Int32 mx)
    {
        var p = BigInteger.One;
        for (Int32 i = x; i <= mx; i += dx)
            p *= i;
        return p;
    }
    
    static BigInteger Catalan(Int32 n)
    {
        Int32 c = n / 2;
        Int32 d = n % 2;
        Int32 m = n - c;
        
        Int32 g = 0;
        for (Int32 i = m; (i /= 2) > 0; )
            g += i;
        
        Int32 k = 1 << (c - g);
        BigInteger top = k * Product(n - d + 3, 2, n * 2);
        
        BigInteger bot = 1;
        for (Int32 i = m; i > 0; i /= 2)
            bot *= Product(1, 2, i);
        
        return top / bot;
    }
    
    public static void Main()
    {
        var ln = Console.ReadLine();
        var n = Int32.Parse(ln);
        
        var c = Catalan(n + 1);
        
        Console.WriteLine(c);
    }
}