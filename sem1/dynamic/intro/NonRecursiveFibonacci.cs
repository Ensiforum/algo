using System;

namespace algo
{
    public class Fibonacci
    {
        public static int fib(int n)
        {
            if (n < 0)
            {
                throw new ArgumentException();
            }
            
            if (n <= 1)
            {
                return n;
            }

            int prelast = 0;
            int last = 1;

            for (int i = 2; i <= n; i++)
            {
                int nextFib = prelast + last;
                prelast = last;
                last = nextFib;
            }

            return last;
        }
    }
}