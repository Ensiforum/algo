# Python3 program for the
# above approach
def foo():

	# Some code here
	pass

# Returns both 0 and 1
# with 50% probability
def my_fun():

	val1, val2 = foo(), foo()
	
	if val1 ^ val2:
	
		# Will reach here with
		# (0.24 + 0.24) probability
		return val1
	
	# Will reach here with
	# (1 - 0.24 - 0.24) probability
	return my_fun()

# Driver Code
if __name__ == '__main__':
	print(my_fun())

# This code is contributed by sgshah2
