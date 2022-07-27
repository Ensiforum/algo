<script>
// A Javascript program to implement Manacher’s Algorithm

function findLongestPalindromicString(text)
{
	let N = text.length;
	if(N == 0)
		return;
	
	// Position count
	N = 2 * N + 1;
	
	// LPS Length Array
	let L = new Array(N);
	L[0] = 0;
	L[1] = 1;
	
	// centerPosition
	let C = 1;
	
	// centerRightPosition
	let R = 2;
	
	// currentRightPosition
	let i = 0;
	
	// currentLeftPosition
	let iMirror;
	let expand = -1;
	let diff = -1;
	let maxLPSLength = 0;
	let maxLPSCenterPosition = 0;
	let start = -1;
	let end = -1;
	
	// Uncomment it to print LPS Length array
	// printf("%d %d ", L[0], L[1]);
	for (i = 2; i < N; i++)
	{
		// Get currentLeftPosition iMirror
		// for currentRightPosition i
		iMirror = 2 * C - i;
		
		// Reset expand - means no
		// expansion required
		expand = 0;
		diff = R - i;
		
		// If currentRightPosition i is
		// within centerRightPosition R
		if(diff >= 0)
		{
			
			// Case 1
			if(L[iMirror] < diff)
				L[i] = L[iMirror];
				
			// Case 2
			else if(L[iMirror] == diff && R == N - 1)
				L[i] = L[iMirror];
			
			// Case 3
			else if(L[iMirror] == diff && R < N - 1)
			{
					L[i] = L[iMirror];
					
					// Expansion required
					expand = 1;
			}
			
			// Case 4
			else if(L[iMirror] > diff)
			{
				L[i] = diff;
				
				// Expansion required
				expand = 1;
			}
		}
		else
		{
			L[i] = 0;
			
			// Expansion required
			expand = 1;
		}
		
		if (expand == 1)
		{
			
			// Attempt to expand palindrome centered
			// at currentRightPosition i. Here for odd
			// positions, we compare characters and
			// if match then increment LPS Length by ONE
			// If even position, we just increment LPS
			// by ONE without any character comparison
			
			
				while (((i + L[i]) < N &&
						(i - L[i]) > 0) &&
					(((i + L[i] + 1) % 2 == 0) ||
					(text[Math.floor((i + L[i] + 1) / 2)] ==
						text[Math.floor((i - L[i] - 1) / 2)])))
				{
					L[i]++;
				}
			
			
		}
		
		// Track maxLPSLength
		if(L[i] > maxLPSLength)
		{
			maxLPSLength = L[i];
			maxLPSCenterPosition = i;
		}

		// If palindrome centered at
		// currentRightPosition i expand
		// beyond centerRightPosition R,
		// adjust centerPosition C based
		// on expanded palindrome.
		if (i + L[i] > R)
		{
			C = i;
			R = i + L[i];
		}
		
		//Uncomment it to print LPS Length array
		//System.out.print("%d ", L[i]);
	}
	
	start = (maxLPSCenterPosition -
			maxLPSLength) / 2;
	end = start + maxLPSLength - 1;
	
	//System.out.print("start: %d end: %d\n",
	//				 start, end);
	document.write("LPS of string is " +
					text + " : ");
	
	for(i = start; i <= end; i++)
		document.write(text[i]);
	document.write("<br>");
}

// Driver code

let text1="babcbabcbaccba";
findLongestPalindromicString(text1);

let text2="abaaba";
findLongestPalindromicString(text2);

let text3= "abababa";
findLongestPalindromicString(text3);

let text4="abcbabcbabcba";
findLongestPalindromicString(text4);

let text5="forgeeksskeegfor";
findLongestPalindromicString(text5);

let text6="caba";
findLongestPalindromicString(text6);

let text7="abacdfgdcaba";
findLongestPalindromicString(text7);

let text8="abacdfgdcabba";
findLongestPalindromicString(text8);

let text9="abacdedcaba";
findLongestPalindromicString(text9);


// source: https://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-3-2/
</script>
 
