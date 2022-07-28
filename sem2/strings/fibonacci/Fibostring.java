// Java program of the above approach
import java.util.*;

class GFG{

// Function that returns true if
// Fibonacci sequence is found
static boolean splitIntoFibonacciHelper(int pos,
										String S,
							ArrayList<Long> seq)
{
	
	// Base condition:
	// If pos is equal to length of S
	// and seq length is greater than 3
	if (pos == S.length() && (seq.size() >= 3))
	{

		// Return true
		return true;
	}

	// Stores current number
	long num = 0;

	for(int i = pos; i < S.length(); i++)
	{
		
		// Add current digit to num
		num = num * 10 + (S.charAt(i) - '0');

		// Avoid integer overflow
		if (num > Integer.MAX_VALUE)
			break;

		// Avoid leading zeros
		if (S.charAt(pos) == '0' && i > pos)
			break;

		// If current number is greater
		// than last two number of seq
		if (seq.size() > 2 &&
		(num > ((long)seq.get(seq.size() - 1) +
				(long)seq.get(seq.size() - 2))))
			break;

		// If seq length is less
		// 2 or current number is
		// is equal to the last
		// two of the seq
		if (seq.size() < 2 ||
			(num == ((long)seq.get(seq.size() - 1) +
					(long)seq.get(seq.size() - 2))))
		{
			
			// Add to the seq
			seq.add(num);

			// Recur for i+1
			if (splitIntoFibonacciHelper(i + 1,
										S, seq))
				return true;

			// Remove last added number
			seq.remove(seq.size() - 1);
		}
	}
	
	// If no sequence is found
	return false;
}

// Function that prints the Fibonacci
// sequence from the split of string S
static void splitIntoFibonacci(String S)
{
	
	// Initialize a vector to
	// store the sequence
	ArrayList<Long> seq = new ArrayList<>();

	// Call helper function
	splitIntoFibonacciHelper(0, S, seq);

	// If sequence length is
	// greater than 3
	if (seq.size() >= 3)
	{
		
		// Print the sequence
		for (int i = 0; i < seq.size(); i++)
			System.out.print(seq.get(i) + " ");
	}

	// If no sequence is found
	else
	{

		// Print -1
		System.out.print("-1");
	}
}

// Driver code
public static void main(String[] args)
{
	
	// Given String
	String S = "11235813";
	
	// Function Call
	splitIntoFibonacci(S);
}
}

// This code is contributed by offbeat
