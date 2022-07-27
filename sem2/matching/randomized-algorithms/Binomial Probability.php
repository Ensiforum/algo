<?php
// php program to compute Binomial
// Probability

// function to calculate nCr i.e.,
// number of ways to choose r out
// of n objects
function nCr($n, $r)
{
	
	// Since nCr is same as nC(n-r)
	// To decrease number of iterations
	if ($r > $n / 2)
		$r = $n - $r;

	$answer = 1;
	for ($i = 1; $i <= $r; $i++) {
		$answer *= ($n - $r + $i);
		$answer /= $i;
	}

	return $answer;
}

// function to calculate binomial r.v.
// probability
function binomialProbability($n, $k, $p)
{
	return nCr($n, $k) * pow($p, $k) *
				pow(1 - $p, $n - $k);
}

// Driver code
	$n = 10;
	$k = 5;
	$p = 1.0 / 3;

	$probability =
		binomialProbability($n, $k, $p);

	echo "Probability of " . $k;
	echo " heads when a coin is tossed "
									. $n;
	echo " times where probability of "
				. "each head is " . $p ;
	echo " is = " . $probability ;

// This code is contributed by nitin mittal.
?>
