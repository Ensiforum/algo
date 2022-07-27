// Java program to demonstrate working of
// Meet in the Middle algorithm for
// maximum subset sum problem
import java.util.*;
import java.lang.*;
import java.io.*;

class Main{
	
static long X[] = new long[2000005];
static long Y[] = new long[2000005];

// Find all possible sum of elements of a[]
// and store in x[]
static void calcsubarray(long a[],long x[],
						int n, int c)
{
	for(int i = 0; i < (1 << n); i++)
	{
		long s = 0;
		for(int j = 0; j < n; j++)
			if ((i & (1 << j)) == 1)
				s += a[j + c];
				
		x[i] = s;
	}
}

// Returns the maximum possible sum
// less or equal to S
static long solveSubsetSum(long a[], int n, long S)
{
	
	// Compute all subset sums of first and second
	// halves
	calcsubarray(a, X, n / 2, 0);
	calcsubarray(a, Y, n - n / 2, n / 2);
	
	int size_X = 1 << (n / 2);
	int size_Y = 1 << (n - n / 2);
	
	// Sort Y (we need to do doing
	// binary search in it)
	Arrays.sort(Y);
	
	// To keep track of the maximum sum
	// of a subset such that the maximum
	// sum is less than S
	long max = 0;
	
	// Traverse all elements of X and do
	// Binary Search for a pair in Y with
	// maximum sum less than S.
	for(int i = 0; i < size_X; i++)
	{
		if (X[i] <= S)
		{
			
			// lower_bound() returns the first address
			// which has value greater than or equal to
			// S-X[i].
			int p = lower_bound(Y, S - X[i]);
	
			// If S-X[i] was not in array Y then
			// decrease p by 1
			if (p == size_Y || Y[p] != (S - X[i]))
				p--;
	
			if ((Y[p] + X[i]) > max)
				max = Y[p] + X[i];
		}
	}
	return max;
}

static int lower_bound(long a[], long x)
{
	
	// x is the target value or key
	int l = -1, r = a.length;
	while (l + 1 < r)
	{
		int m = (l + r) >>> 1;
		if (a[m] >= x)
			r = m;
		else
			l = m;
	}
	return r;
}


}
