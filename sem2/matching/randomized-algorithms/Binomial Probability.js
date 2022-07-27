<script>

// Javascript program to compute Binomial Probability

	// function to calculate nCr i.e., number of
	// ways to choose r out of n objects
	function nCr(n, r)
	{
		// Since nCr is same as nC(n-r)
		// To decrease number of iterations
		if (r > n / 2)
			r = n - r;
		
		let answer = 1;
		for (let i = 1; i <= r; i++) {
			answer *= (n - r + i);
			answer /= i;
		}
		
		return answer;
	}
		
	// function to calculate binomial r.v. probability
	function binomialProbability(n, k, p)
	{
		return nCr(n, k) * Math.pow(p, k) *
						Math.pow(1 - p, n - k);
	}
	
// driver program
		let n = 10;
		let k = 5;
		let p = 1.0 / 3;
		
		let probability = binomialProbability(n, k, p);
			
		document.write("Probability of " +k);
		document.write(" heads when a coin is tossed " +n);
		document.write(" times where probability of each head is " +p);
		document.write( " is = " + probability );

// This code is contributed by code_hunt.
</script>
