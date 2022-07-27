<?php
// PHP Program to find nth
// term of Thue-Morse sequence.

// Return the complement
// of the binary string.
function complement($s)
{
	$comps = "";

	// finding the complement
	// of the string.
	for ($i = 0;
		$i < strlen($s); $i++)
	{

		// if character is
		// 0, append 1
		if ($s[$i] == '0')
			$comps .= '1';

		// if character is
		// 1, append 0.
		else
			$comps .= '0';
	}

	return $comps;
}

// Return the nth term
// of Thue-Morse sequence.
function nthTerm($n)
{
	// Initialing the
	// string to 0
	$s = "0";

	// Running the loop
	// for n - 1 time.
	for ($i = 1; $i < $n; $i++)

		// appending the complement of
		// the string to the string.
		$s .= complement($s);
	

	return $s;
}

// Driven Code
$n = 4;
echo nthTerm($n);

// source: https://www.geeksforgeeks.org/thue-morse-sequence/
?>
