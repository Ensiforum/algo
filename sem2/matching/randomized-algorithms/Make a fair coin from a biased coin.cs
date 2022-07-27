using System;

class GFG {

	// given method that returns 0
	// with 60% probability and 1 with 40%
	static int foo()
	{
		// some code here
	}

	// returns both 0 and 1 with 50% probability
	static int my_fun()
	{
		int val1 = foo();
		int val2 = foo();
		if (val1 == 0 && val2 == 1)
			return 0; // Will reach here with
					// 0.24 probability
		if (val1 == 1 && val2 == 0)
			return 1; // Will reach here with
					// 0.24 probability
		return my_fun(); // will reach here with
						// (1 - 0.24 - 0.24) probability
	}

	// Driver Code
	static public void Main() { Console.Write(my_fun()); }
}

// This is code is contributed
// by ShubhamCoder
