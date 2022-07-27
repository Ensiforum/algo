<script>

// Given method that returns 0 with
// 60% probability and 1 with 40%
function foo()
{
	// Some code here
}

// Returns both 0 and 1 with
// 50% probability
function my_fun()
{
	var val1 = foo();
	var val2 = foo();
	
	if (val1 == 0 && val2 == 1)
		return 0; // Will reach here with
				// 0.24 probability
				
	if (val1 == 1 && val2 == 0)
		return 1; // Will reach here with
				// 0.24 probability
				
	return my_fun(); // Will reach here with
					// (1 - 0.24 - 0.24) probability
}

// Driver Code
document.write(my_fun());

// This code is contributed by noob2000

</script>
