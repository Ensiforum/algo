<script>

// Javascript program to Generate integer from
// 1 to 5 with equal probability

	// given method that returns 1 to 5 with equal probability
	function foo()
	{
		// some code here
		return 0;
	}
	
	// returns 1 to 7 with equal probability
	function my_rand()
	{
		let i;
		i = 5*foo() + foo() - 5;
		if (i < 22)
			return i%7 + 1;
		return my_rand();
	}
	
	// Driver code
	document.write(my_rand());
	
	// This code is contributed by rag2127
	
</script>
