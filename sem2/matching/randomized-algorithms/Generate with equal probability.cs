// C# program to Generate integer from
// 1 to 5 with equal probability
using System;
class GfG
{

// given method that returns 1 to 5 with equal probability
static int foo()
{
	// some code here
	return 0;
}

// returns 1 to 7 with equal probability
public static int my_rand()
{
	int i;
	i = 5*foo() + foo() - 5;
	if (i < 22)
		return i%7 + 1;
	return my_rand();
}

// Driver code
public static void Main () {

	Console.Write(my_rand()+"\n");
}
}
