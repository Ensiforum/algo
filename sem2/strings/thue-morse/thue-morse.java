// Java Program to find nth
// term of Thue-Morse sequence.

class GFG
{
	// Return the complement
	// of the binary String.
	static String complement(String s)
	{
		String comps = "";
	
		// finding the complement
		// of the String.
		for (int i = 0; i < s.length(); i++)
		{
	
			// if character is 0,
			// append 1
			if (s.charAt(i) == '0')
				comps += '1';
	
			// if character is 1,
			// append 0.
			else
				comps += '0';
		}
	
		return comps;
	}
	
	// Return the nth term
	// of Thue-Morse sequence.
	static String nthTerm(int n)
	{
		// Initialing the
		// String to 0
		String s = "0";
	
		// Running the loop
		// for n - 1 time.
		for (int i = 1; i < n; i++)
	
			// appending the complement of
			// the String to the String.
			s += complement(s);
		
	
		return s;
	}
	
	// Driven Code
public static void main(String[] args)
	{
		int n = 4;
		System.out.print(nthTerm(n));
	}
}

// source: https://www.geeksforgeeks.org/thue-morse-sequence/

