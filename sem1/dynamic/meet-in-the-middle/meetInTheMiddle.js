<script>
// Javascript program to demonstrate working of
// Meet in the Middle algorithm for
// maximum subset sum problem
let X = new Array(2000005);
let Y = new Array(2000005);
for(let i = 0; i < 2000005; i++)
{
	X[i] = 0;
	Y[i] = 0;
}

// Find all possible sum of elements of a[]
// and store in x[]
function calcsubarray(a, x, n, c)
{
	for(let i = 0; i < (1 << n); i++)
	{
		let s = 0;
		for(let j = 0; j < n; j++)
			if ((i & (1 << j)) == 1)
				s += a[j + c];
				
		x[i] = s;
	}
}

// Returns the maximum possible sum
// less or equal to S
function solveSubsetSum(a,n,S)
{
	// Compute all subset sums of first and second
	// halves
	calcsubarray(a, X, Math.floor(n / 2), 0);
	calcsubarray(a, Y, n - Math.floor(n / 2), Math.floor(n / 2));
	
	let size_X = 1 << Math.floor(n / 2);
	let size_Y = 1 << (n - Math.floor(n / 2));
	
	// Sort Y (we need to do doing
	// binary search in it)
	Y.sort(function(a,b){return a-b;});
	
	// To keep track of the maximum sum
	// of a subset such that the maximum
	// sum is less than S
	let max = 0;
	
	// Traverse all elements of X and do
	// Binary Search for a pair in Y with
	// maximum sum less than S.
	for(let i = 0; i < size_X; i++)
	{
		if (X[i] <= S)
		{
			
			// lower_bound() returns the first address
			// which has value greater than or equal to
			// S-X[i].
			let p = lower_bound(Y, S - X[i]);
	
			// If S-X[i] was not in array Y then
			// decrease p by 1
			if (p == size_Y || Y[p] != (S - X[i]))
				p--;
	
			if ((Y[p] + X[i]) > max)
				max = Y[p] + X[i];
		}
	}
	return max;
}

function lower_bound(a,x)
{
	// x is the target value or key
	let l = -1, r = a.length;
	while (l + 1 < r)
	{
		let m = (l + r) >>> 1;
		if (a[m] >= x)
			r = m;
		else
			l = m;
	}
	return r;
}



</script>
