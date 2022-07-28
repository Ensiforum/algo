<script>

// Fibonacci Series using Dynamic Programming

	function fib(n)
	{
		/* Declare an array to store Fibonacci numbers. */
		let f = new Array(n+2); // 1 extra to handle case, n = 0
		let i;
		/* 0th and 1st number of the series are 0 and 1*/
		f[0] = 0;
		f[1] = 1;
		for (i = 2; i <= n; i++)
		{
			/* Add the previous 2 numbers in the series
			and store it */
			f[i] = f[i-1] + f[i-2];
		}
		return f[n];
	}
	let n=9;
	document.write(fib(n));
	
	// This code is contributed by avanitrachhadiya2155
	
</script>
