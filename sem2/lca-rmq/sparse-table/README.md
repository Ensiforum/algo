# SPARSE TABLE (ST) ALGORITHM
A better approach is to preprocess RMQ for sub arrays of length 2k using dynamic programming. We will keep an array M[0, N-1][0, logN] where M[i][j] is the index of the minimum value in the sub array starting at i having length 2j. Here is an example:

![image](https://user-images.githubusercontent.com/101459465/180602194-ac7af6e6-8727-4ffa-83b5-bb70f6c2848e.png)

For computing M[i][j] we must search for the minimum value in the first and second half of the interval. It’s obvious that the small pieces have 2j-1 length, so the recurrence is:

![image](https://user-images.githubusercontent.com/101459465/180602196-467185ba-f022-45e1-a319-bcb7d7623b67.png)

The preprocessing function will look something like this:

  void process2(int M[MAXN][LOGMAXN], int A[MAXN], int N) {
    int i, j;

    //initialize M for the intervals with length 1
    for (i = 0; i < N; i++)
      M[i][0] = i;
    //compute values from smaller to bigger intervals
    for (j = 1; 1 << j <= N; j++)
      for (i = 0; i + (1 << j) - 1 < N; i++)
        if (A[M[i][j - 1]] < A[M[i + (1 << (j - 1))][j - 1]])
          M[i][j] = M[i][j - 1];
        else
          M[i][j] = M[i + (1 << (j - 1))][j - 1];
  }

Once we have these values preprocessed, let’s show how we can use them to calculate RMQA(i, j). The idea is to select two blocks that entirely cover the interval [i…j] and find the minimum between them. Let k = [log(j - i + 1)]. For computing RMQA(i, j) we can use the following formula:

![image](https://user-images.githubusercontent.com/101459465/180602202-7e480559-1866-4a36-8777-b762827bbaf8.png)

So, the overall complexity of the algorithm is <O(N logN), O(1)>.

source: https://www.topcoder.com/thrive/articles/Range%20Minimum%20Query%20and%20Lowest%20Common%20Ancestor
