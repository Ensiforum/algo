using System;

namespace algo
{
    public class binomial_coefficient
    {
        public static int BinomialCoef(int n, int m)
        {
            int[] buff = new int[n + 1];

            if (m < 0 || m > n)
            {
                throw new ArgumentException();
            }

            if (n <= 1)
            {
                return 1;
            }
            
            buff[0] = 1;
            buff[1] = 1;

            for (int i = 2; i <= n; i++)
            {
                int[] next = new int[n + 1];
                for (int j = 0; j <= i; j++)
                {
                    if (j == 0 || j == i)
                    {
                        next[j] = 1;
                        continue;
                    }

                    next[j] = buff[j - 1] + buff[j];
                }

                buff = next;
            }

            return buff[m];
        }
    }
}