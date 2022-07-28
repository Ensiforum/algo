<?php
// PHP program to find maximum
// achievable value with a
// knapsack of weight W and
// multiple instances allowed.

// Returns the maximum value
// with knapsack of W capacity
function unboundedKnapsack($W, $n,
						$val, $wt)
{
	// dp[i] is going to store
	// maximum value with
	// knapsack capacity i.
	for($i = 0; $i <= $W; $i++)
		$dp[$i] = 0;

	$ans = 0;
	
	// Fill dp[] using above
	// recursive formula
	for ($i = 0; $i <= $W; $i++)
	for ($j = 0; $j < $n; $j++)
		if ($wt[$j] <= $i)
			$dp[$i] = max($dp[$i],
						$dp[$i - $wt[$j]] +
								$val[$j]);

	return $dp[$W];
}

// Driver Code
$W = 100;
$val = array(10, 30, 20);
$wt = array(5, 10, 15);
$n = count($val); //sizeof($val)/sizeof($val[0]);

echo unboundedKnapsack($W, $n,
					$val, $wt);

// This code is contributed
// by shiv_bhakt
?>
