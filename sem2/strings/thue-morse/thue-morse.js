<script>

// JavaScript Program to find nth
// term of Thue-Morse sequence.

	// Return the complement
	// of the binary string.
	function complement(s)
	{
		let comps = "";
	
		// finding the complement
		// of the string.
		for (let i = 0; i < s.length; i++)
		{
	
			// if character is 0,
			// append 1
			if (s[i] == '0')
				comps += '1';
	
			// if character is 1,
			// append 0.
			else
				comps += '0';
		}
	
		return comps;
	}
	
	// Return the nth term
	// of Thue-Morse sequence.
	function nthTerm(n)
	{
		// Initialing the
		// string to 0
		let s = "0";
	
		// Running the loop
		// for n - 1 time.
		for (let i = 1; i < n; i++)
	
			// appending the complement of
			// the string to the string.
			s += complement(s);
		
	
		return s;
	}

// Driver program

		let n = 4;
		document.write(nthTerm(n));
		
		// source: https://www.geeksforgeeks.org/thue-morse-sequence/
</script>
