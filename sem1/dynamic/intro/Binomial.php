<?php
// A Dynamic Programming based
// solution that uses table C[][] to
// calculate the Binomial Coefficient

// Returns value of Binomial
// Coefficient C(n, k)
function binomialCoeff( $n, $k)
{
	$C = array(array());
	$i; $j;

	// Calculate value of Binomial
	// Coefficient in bottom up manner
	for ($i = 0; $i <= $n; $i++)
	{
		for ($j = 0; $j <= min($i, $k); $j++)
		{
			
			// Base Cases
			if ($j == 0 || $j == $i)
				$C[$i][$j] = 1;

			// Calculate value using
			// previously stored values
			else
				$C[$i][$j] = $C[$i - 1][$j - 1] +
								$C[$i - 1][$j];
		}
	}

	return $C[$n][$k];
}

	// Driver Code
	$n = 5;
	$k = 2;
	echo "Value of C(" ,$n," ",$k, ") is"," "
				, binomialCoeff($n, $k) ;

// This code is contributed by anuj_67.
?>
