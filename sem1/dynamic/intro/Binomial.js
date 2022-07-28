<script>

// A Dynamic Programming based
// solution that uses table C to
// calculate the Binomial Coefficient

// Returns value of Binomial
// Coefficient C(n, k)
function binomialCoeff(n, k)
{
	var C = Array(n + 1).fill(0).map(
	x => Array(k + 1).fill(0));;
	var i, j;

	// Calculate value of Binomial
	// Coefficient in bottom up manner
	for(i = 0; i <= n; i++)
	{
		for(j = 0; j <= min(i, k); j++)
		{
			
			// Base Cases
			if (j == 0 || j == i)
				C[i][j] = 1;

			// Calculate value using
			// previously stored values
			else
				C[i][j] = C[i - 1][j - 1] +
						C[i - 1][j];
		}
	}
	return C[n][k];
}

// A utility function to return
// minimum of two integers
function min(a, b)
{
	return (a < b) ? a : b;
}

// Driver code
var n = 5, k = 2;
document.write("Value of C(" + n + "," + k +
					") is " + binomialCoeff(n, k));

// This code is contributed by 29AjayKumar

</script>
