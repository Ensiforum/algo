<script>
	// Javascript program to find maximum achievable
	// value with a knapsack of weight W and
	// multiple instances allowed.
	
	function max(i, j)
	{
			return (i > j) ? i : j;
	}
	
	// Returns the maximum value
	// with knapsack of W capacity
	function unboundedKnapsack(W, n, val, wt)
	{
		
		// dp[i] is going to store maximum value
		// with knapsack capacity i.
		let dp = new Array(W + 1);
		dp.fill(0);
		
		// Fill dp[] using above recursive formula
		for(let i = 0; i <= W; i++){
			for(let j = 0; j < n; j++){
				if(wt[j] <= i){
					dp[i] = Math.max(dp[i], dp[i - wt[j]] + val[j]);
				}
			}
		}
		return dp[W];
	}
	
	let W = 100;
	let val = [10, 30, 20];
	let wt = [5, 10, 15];
	let n = val.length;
	document.write(unboundedKnapsack(W, n, val, wt));
	
</script>
