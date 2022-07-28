<script>
	// Javascript program of the above approach
	
	// Function that returns true if
	// Fibonacci sequence is found
	function splitIntoFibonacciHelper(pos, S, seq)
	{

		// Base condition:
		// If pos is equal to length of S
		// and seq length is greater than 3
		if (pos == S.length && (seq.length >= 3))
		{

			// Return true
			return true;
		}

		// Stores current number
		let num = 0;

		for(let i = pos; i < S.length; i++)
		{

			// Add current digit to num
			num = num * 10 + (S[i] - '0');

			// Avoid integer overflow
			if (num > Number.MAX_VALUE)
				break;

			// Avoid leading zeros
			if (S[pos] == '0' && i > pos)
				break;

			// If current number is greater
			// than last two number of seq
			if (seq.length> 2 &&
			(num > (seq[seq.length - 1] +
					seq[seq.length - 2])))
				break;

			// If seq length is less
			// 2 or current number is
			// is equal to the last
			// two of the seq
			if (seq.length < 2 ||
			(num == (seq[seq.length - 1] +
						seq[seq.length - 2])))
			{

				// Add to the seq
				seq.push(num);

				// Recur for i+1
				if (splitIntoFibonacciHelper(i + 1, S, seq))
					return true;

				// Remove last added number
				seq.pop();
			}
		}

		// If no sequence is found
		return false;
	}

	// Function that prints the Fibonacci
	// sequence from the split of string S
	function splitIntoFibonacci(S)
	{

		// Initialize a vector to
		// store the sequence
		let seq = [];

		// Call helper function
		splitIntoFibonacciHelper(0, S, seq);

		// If sequence length is
		// greater than 3
		if (seq.length >= 3)
		{

			// Print the sequence
			for(let i = 0; i < seq.length; i++)
				document.write(seq[i] + " ");
		}

		// If no sequence is found
		else
		{

			// Print -1
			document.write("-1");
		}
	}
	
	// Given String
	let S = "11235813";
	
	// Function call
	splitIntoFibonacci(S);

// This code is contributed by suresh07.
</script>
