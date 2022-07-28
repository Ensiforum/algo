# Python3 program of the above approach
import sys

# Function that returns true if
# Fibonacci sequence is found
def splitIntoFibonacciHelper(pos, S, seq):

	# Base condition:
	# If pos is equal to length of S
	# and seq length is greater than 3
	if (pos == len(S) and (len(seq) >= 3)):

		# Return true
		return True

	# Stores current number
	num = 0
	
	for i in range(pos, len(S)):

		# Add current digit to num
		num = num * 10 + (ord(S[i]) - ord('0'))

		# Avoid integer overflow
		if (num > sys.maxsize):
			break

		# Avoid leading zeros
		if (ord(S[pos]) == ord('0') and i > pos):
			break

		# If current number is greater
		# than last two number of seq
		if (len(seq) > 2 and
				(num > (seq[-1] +
						seq[len(seq) - 2]))):
			break

		# If seq length is less
		# 2 or current number is
		# is equal to the last
		# two of the seq
		if (len(seq) < 2 or
		(num == (seq[-1] +
					seq[len(seq) - 2]))):

			# Add to the seq
			seq.append(num)

			# Recur for i+1
			if (splitIntoFibonacciHelper(
				i + 1, S, seq)):
				return True

			# Remove last added number
			seq.pop()

	# If no sequence is found
	return False

# Function that prints the Fibonacci
# sequence from the split of string S
def splitIntoFibonacci(S):
	
	# Initialize a vector to
	# store the sequence
	seq = []

	# Call helper function
	splitIntoFibonacciHelper(0, S, seq)

	# If sequence length is
	# greater than 3
	if (len(seq) >= 3):

		# Print the sequence
		for i in seq:
			print(i, end = ' ')
			
	# If no sequence is found
	else:

		# Print -1
		print(-1, end = '')
		
# Driver Code
if __name__=='__main__':
	
	# Given String
	S = "11235813"

	# Function Call
	splitIntoFibonacci(S)

# This code is contributed by pratham76
