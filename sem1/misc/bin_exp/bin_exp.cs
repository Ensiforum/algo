using System;

namespace algo
{
    public class bin_exp
    {
        public static int[,] MultiplyMatrices(int[,] first, int[,] second)
        {
            if (first.GetLength(1) != second.GetLength(0))
            {
                throw new ArgumentException("Matrices cannot be multiplied");
            }

            int[,] result = new int[first.GetLength(0), second.GetLength(1)];

            for (int i = 0; i < first.GetLength(0); i++)
            {
                for (int j = 0; j < second.GetLength(1); j++)
                {
                    for (int k = 0; k < first.GetLength(1); k++)
                    {
                        result[i, j] += first[i, k] * second[k, j];
                    }
                }
            }

            return result;
        }
        
        

        public static int[,] PowMatrix(int[,] matrix, int pow)
        {
            if (matrix.GetLength(0) != matrix.GetLength(1))
            {
                throw new ArgumentException("Matrix cannot be powered");
            }
            
            if (pow == 1)
            {
                return matrix;
            }

            if (pow % 2 == 0)
            {
                var temp = PowMatrix(matrix, pow / 2);
                return MultiplyMatrices(temp, temp);
            }
            return MultiplyMatrices(PowMatrix(matrix, pow - 1), matrix);
        }
    }
}