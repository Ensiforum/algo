# Python program to demonstrate working of Meet in the
# Middle algorithm for maximum subset sum problem.
from typing import List
import bisect
X = [0] * 2000005
Y = [0] * 2000005

# Find all possible sum of elements of a[] and store
# in x[]
def calcsubarray(a: List[int], x: List[int], n: int, c: int) -> None:
	for i in range((1 << n)):
		s = 0
		for j in range(n):
			if (i & (1 << j)):
				s += a[j + c]
		x[i] = s

# Returns the maximum possible sum less or equal to S
def solveSubsetSum(a: List[int], n: int, S: int) -> int:
	global Y
	
	# Compute all subset sums of first and second
	# halves
	calcsubarray(a, X, n // 2, 0)
	calcsubarray(a, Y, n - n // 2, n // 2)
	size_X = 1 << (n // 2)
	size_Y = 1 << (n - n // 2)

	# Sort Y (we need to do doing binary search in it)
	YY = Y[:size_Y]
	YY.sort()
	Y = YY

	# To keep track of the maximum sum of a subset
	# such that the maximum sum is less than S
	maxx = 0

	# Traverse all elements of X and do Binary Search
	# for a pair in Y with maximum sum less than S.
	for i in range(size_X):

		if (X[i] <= S):

			# lower_bound() returns the first address
			# which has value greater than or equal to
			# S-X[i].
			p = bisect.bisect_left(Y, S - X[i])

			# If S-X[i] was not in array Y then decrease
			# p by 1
			if (p == size_Y or (p < size_Y and Y[p] != (S - X[i]))):
				p -= 1
			if ((Y[p] + X[i]) > maxx):
				maxx = Y[p] + X[i]
	return maxx


