// C# program to compute Binomial
// Probability.
using System;

class GFG {
	
	// function to calculate nCr
	// i.e., number of ways to
	// choose r out of n objects
	static int nCr(int n, int r)
	{
		
		// Since nCr is same as
		// nC(n-r) To decrease
		// number of iterations
		if (r > n / 2)
			r = n - r;
	
		int answer = 1;
		for (int i = 1; i <= r; i++)
		{
			answer *= (n - r + i);
			answer /= i;
		}
	
		return answer;
	}
	
	// function to calculate binomial
	// r.v. probability
	static float binomialProbability(
				int n, int k, float p)
	{
		return nCr(n, k) *
				(float)Math.Pow(p, k)
				* (float)Math.Pow(1 - p,
								n - k);
	}
	
	// Driver code
	public static void Main()
	{
		int n = 10;
		int k = 5;
		float p = (float)1.0 / 3;
	
		float probability =
			binomialProbability(n, k, p);
		
		Console.Write("Probability of "
									+ k);
		Console.Write(" heads when a coin "
					+ "is tossed " + n);
		Console.Write(" times where "
		+ "probability of each head is "
									+ p);
		Console.Write( " is = "
						+ probability );
	}
}

// This code is contributed by nitin mittal.
