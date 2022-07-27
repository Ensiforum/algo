# Python3 Program to find nth term of
# Thue-Morse sequence.

# Return the complement of the
# binary string.
def complement(s):
	comps = "";

	# finding the complement
	# of the string.
	for i in range(len(s)):

		# if character is 0, append 1
		if (s[i] == '0'):
			comps += '1';

		# if character is 1, append 0.
		else:
			comps += '0';

	return comps;

# Return the nth term of
# Thue-Morse sequence.
def nthTerm(n):

	# Initialing the string to 0
	s = "0";

	# Running the loop for n - 1 time.
	for i in range(1, n):

		# appending the complement of
		# the string to the string.
		s += complement(s);
	
	return s;

# Driver Code
n = 4;
print(nthTerm(n));

# source: https://www.geeksforgeeks.org/thue-morse-sequence/
