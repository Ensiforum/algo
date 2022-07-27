// C++ program to compute Binomial Probability
#include <iostream>
#include <cmath>
using namespace std;

// function to calculate nCr i.e., number of
// ways to choose r out of n objects
int nCr(int n, int r)
{
	// Since nCr is same as nC(n-r)
	// To decrease number of iterations
	if (r > n / 2)
		r = n - r;

	int answer = 1;
	for (int i = 1; i <= r; i++) {
		answer *= (n - r + i);
		answer /= i;
	}

	return answer;
}

// function to calculate binomial r.v. probability
float binomialProbability(int n, int k, float p)
{
	return nCr(n, k) * pow(p, k) *
				pow(1 - p, n - k);
}

// Driver code
int main()
{

	int n = 10;
	int k = 5;
	float p = 1.0 / 3;

	float probability = binomialProbability(n, k, p);

	cout << "Probability of " << k;
	cout << " heads when a coin is tossed " << n;
	cout << " times where probability of each head is " << p << endl;
	cout << " is = " << probability << endl;
}
