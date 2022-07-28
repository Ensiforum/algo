<script>

/* A Top-Down DP implementation of LCS problem */

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
function lcs(X, Y, m, n, dp)
{
	if (m == 0 || n == 0)
		return 0;
	if (X[m - 1] == Y[n - 1])
		return dp[m][n] = 1 + lcs(X, Y, m - 1, n - 1, dp);

	if (dp[m][n] != -1) {
		return dp[m][n];
	}
	return dp[m][n] = Math.max(lcs(X, Y, m, n - 1, dp),
						lcs(X, Y, m - 1, n, dp));
}

/* Driver code */

let X = "AGGTAB";
let Y = "GXTXAYB";

let m = X.length;
let n = Y.length;
let dp = new Array(m + 1);
for(let i = 0; i < m + 1; i++)
{
	dp[i] = new Array(n + 1).fill(-1);
}
document.write("Length of LCS is " + lcs(X, Y, m, n, dp));

// This code is contributed by shinjanpatra

</script>
