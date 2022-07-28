// C# program of the above approach
using System;
using System.Collections;
using System.Collections.Generic;

class GFG{
	
// Function that returns true if
// Fibonacci sequence is found
static bool splitIntoFibonacciHelper(int pos,
									string S,
								ArrayList seq)
{
	
	// Base condition:
	// If pos is equal to length of S
	// and seq length is greater than 3
	if (pos == S.Length && (seq.Count >= 3))
	{

		// Return true
		return true;
	}

	// Stores current number
	long num = 0;

	for(int i = pos; i < S.Length; i++)
	{
		
		// Add current digit to num
		num = num * 10 + (S[i] - '0');

		// Avoid integer overflow
		if (num > Int64.MaxValue)
			break;
	
		// Avoid leading zeros
		if (S[pos] == '0' && i > pos)
			break;

		// If current number is greater
		// than last two number of seq
		if (seq.Count> 2 &&
		(num > ((long)seq[seq.Count - 1] +
				(long)seq[seq.Count - 2])))
			break;

		// If seq length is less
		// 2 or current number is
		// is equal to the last
		// two of the seq
		if (seq.Count < 2 ||
		(num == ((long)seq[seq.Count - 1] +
					(long)seq[seq.Count - 2])))
		{
			
			// Add to the seq
			seq.Add(num);

			// Recur for i+1
			if (splitIntoFibonacciHelper(i + 1,
										S, seq))
				return true;

			// Remove last added number
			seq.Remove(seq.Count - 1);
		}
	}
	
	// If no sequence is found
	return false;
}

// Function that prints the Fibonacci
// sequence from the split of string S
static void splitIntoFibonacci(string S)
{
	
	// Initialize a vector to
	// store the sequence
	ArrayList seq = new ArrayList();

	// Call helper function
	splitIntoFibonacciHelper(0, S, seq);

	// If sequence length is
	// greater than 3
	if (seq.Count >= 3)
	{
		
		// Print the sequence
		for(int i = 0; i < seq.Count; i++)
			Console.Write(seq[i] + " ");
	}

	// If no sequence is found
	else
	{
		
		// Print -1
		Console.Write("-1");
	}
}

// Driver Code
public static void Main(string[] args)
{
	
	// Given String
	string S = "11235813";
	
	// Function call
	splitIntoFibonacci(S);
}
}

// This code is contributed by rutvik_56
