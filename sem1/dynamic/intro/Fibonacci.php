<?php
//Fibonacci Series using Dynamic
// Programming

function fib( $n)
{
	
	/* Declare an array to store
	Fibonacci numbers. */
	
	// 1 extra to handle case,
	// n = 0
	$f = array();
	$i;
	
	/* 0th and 1st number of the
	series are 0 and 1*/
	$f[0] = 0;
	$f[1] = 1;
	
	for ($i = 2; $i <= $n; $i++)
	{
		
		/* Add the previous 2
		numbers in the series
		and store it */
		$f[$i] = $f[$i-1] + $f[$i-2];
	}
	
	return $f[$n];
}

$n = 9;
echo fib($n);

// This code is contributed by
// anuj_67.
?>
