// Written by Oleksandr Pravosud
// Actually it is just a rewritten code from C++ version

using System;

public class LCS
{
    /// <summary>
    /// Finds the length of LCS for 2 strings
    /// </summary>
    /// <param name="first">First string</param>
    /// <param name="second">Second string</param>
    /// <returns>The LCS length of 2 strings</returns>
    public static int Lcs(string first, string second)
    {
        int m = first.Length;
        int n = second.Length;
        int[,] dp = CreateMatrix(m + 1, n + 1, -1);
        return Lcs(first, second, m, n, dp);
    }
    
    /// <summary>
    /// Finds the length of LCS for 2 strings
    /// </summary>
    /// <param name="first">First string</param>
    /// <param name="second">Second string</param>
    /// <param name="m">
    /// The length of the first string on which it will be processed.
    /// In fact, the right non-inclusive boundary.
    /// </param>
    /// <param name="n">
    /// The length of the second string on which it will be processed.
    /// In fact, the right non-inclusive boundary.
    /// </param>
    /// <param name="dp">Matrix used for dynamic programming</param>
    /// <returns>The length of LCS for first[0..m-1], second[0..n-1]</returns>
    private static int Lcs(string first, string second, int m, int n, int[,] dp)
    {
        if (m == 0 || n == 0)
        {
            return 0;
        }

        if (first[m - 1] == second[n - 1])
        {
            dp[m, n] = 1 + Lcs(first, second, m - 1, n - 1, dp);
            return dp[m, n];
        }

        if (dp[m, n] != -1)
        {
            return dp[m, n];
        }

        dp[m, n] = Math.Max(
            Lcs(first, second, m, n - 1, dp), 
            Lcs(first, second, m - 1, n, dp)
        );
        return dp[m, n];
    }

    /// <summary>
    /// Creates a matrix and fills it with the specified values
    /// </summary>
    /// <param name="verticalLength">Zero dimension length</param>
    /// <param name="horizontalLength">First dimension length</param>
    /// <param name="value">Value to fill the matrix</param>
    /// <returns>The matrix of ints</returns>
    private static int[,] CreateMatrix(int verticalLength, int horizontalLength, int value = 0)
    {
        var matrix = new int[verticalLength, horizontalLength];

        for (int i = 0; i < verticalLength; i++)
        {
            for (int j = 0; j < horizontalLength; j++)
            {
                matrix[i, j] = value;
            }
        }

        return matrix;
    }
}