# Python3 program to Generate integer
# from 1 to 5 with equal probability
# given method that returns 1 to 5
# with equal probability
def foo():

	# some code here
	return 0;

# returns 1 to 7 with equal probability
def my_rand():
	i = 0;
	i = (5 * foo()) + (foo() - 5);
	if (i < 22):
		if(i < 0):
			return (i % 7 - 7) + 1;
		else:
			return (i % 7) + 1;
			
	return my_rand();

# Driver code
if __name__ == '__main__':
	print(my_rand());

# This code contributed by PrinciRaj1992
