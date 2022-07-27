// C# Program to find nth
// term of Thue-Morse sequence.
using System;

class GFG
{
	// Return the complement
	// of the binary string.
	static string complement(string s)
	{
		string comps = "";
	
		// finding the complement
		// of the string.
		for (int i = 0; i < s.Length; i++)
		{
	
			// if character is 0,
			// append 1
			if (s[i] == '0')
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
	static string nthTerm(int n)
	{
		// Initialing the
		// string to 0
		string s = "0";
	
		// Running the loop
		// for n - 1 time.
		for (int i = 1; i < n; i++)
	
			// appending the complement of
			// the string to the string.
			s += complement(s);
		
	
		return s;
	}
	
	// Driven Code
	static void Main()
	{
		int n = 4;
		Console.Write(nthTerm(n));
	}
}

// source: geeksforgeeks.org/thue-morse-sequence/
