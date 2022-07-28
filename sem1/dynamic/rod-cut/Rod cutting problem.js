<script>
	// A Dynamic Programming solution
	// for Rod cutting problem
	
	/* Returns the best obtainable
	price for a rod of length n
	and price[] as prices of
	different pieces */
	function cutRod(price, n)
	{
		let val = new Array(n + 1);
		val[0] = 0;

		// Build the table val[] in
		// bottom up manner and return
		// the last entry from the table
		for (let i = 1; i<=n; i++)
		{
			let max_val = Number.MIN_VALUE;
			for (let j = 0; j < i; j++)
				max_val = Math.max(max_val, price[j] + val[i - j - 1]);
			val[i] = max_val;
		}

		return val[n];
	}
	
	let arr = [1, 5, 8, 9, 10, 17, 17, 20];
	let size = arr.length;
	document.write("Maximum Obtainable Value is " + cutRod(arr, size) + "n");
</script>
