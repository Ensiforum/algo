<h1>String hashing using Polynomial rolling hash function</h1>
<h2>Hash Function</h2>
<p>A Hash function is a function that maps any kind of data of arbitrary size to fixed-size values. The values returned by the function are called Hash Values or digests. There are many popular Hash Functions such as DJBX33A, MD5, and SHA-256. This post will discuss the key features, implementation, advantages and drawbacks of the Polynomial Rolling Hash Function.</p>

<p><i>Note that if two strings are equal, their hash values should also be equal. But the inverse need not be true.</i></p>

<b>The polynomial rolling hash function</b>
<p>Polynomial rolling hash function is a hash function that uses only multiplications and additions. The following is the function:</p>
<img src = "https://www.geeksforgeeks.org/wp-content/ql-cache/quicklatex.com-527c8cfa29551dd21b36d13a2343f285_l3.svg">
<br> <br> or simply, 
<br>
<img src = "https://www.geeksforgeeks.org/wp-content/ql-cache/quicklatex.com-54b5d229f345f66c8f94a6f059c01019_l3.svg">




<br>
Where
<ul>
	<li>The input to the function is a string <b>s</b>  of length <b>n</b>.</li>	
	<li><b>p</b> and <b>m</b> are some positive integers.</li>
	<li>The choice of <b>p</b> and <b>m</b> affects the performance and the security of hash function.</li>
	<li>If the string <b>s</b> consists of only lower-case letters, 
	then <b>p = 31</b> is a good choice.</li>
	<li>Competitive programmers prefer using larger value for <b>p</b>. Examples include <b>29791, 11111, 111111</b></li>
	<li><b>m</b> shall necessarily  be a large prime since the probability of two keys colliding (producing the same hash) is nearly <b>1/m</b>. <b>10^9+7</b> and <b>10^9+9</b> are widely used values for <b>m</b></li>
	<li>The output of the function is the hash value of the string s which ranges between <b>0</b> and <b>(m-1)</b> inclusive.</li>
</ul>

<h2>Collisions in Polynomial Rolling Hash</h2>
<p>Since the output of the Hash function is an integer in the range <b>[0, m)</b>, there are high chances for two strings producing the same hash value.
We can guarantee a collision within a very small domain. Consider a set of strings, <b>S</b>, consisting of only lower-case letters, such that the length of any string in <b>S</b>   doesn’t exceed 7. We have <img src = "https://www.geeksforgeeks.org/wp-content/ql-cache/quicklatex.com-577203ca433b8af20eba7a6ae1bba5cf_l3.svg">. Since the range of the Hash Function is <b>[0, m)</b>, one-one mapping is impossible. Hence, we can guarantee a collision by arbitrarily generating two strings whose length doesn’t exceed 7.
</p>

<h2>Collision resolution</h2>
<p>We can note that the value of <b>m</b> affects the chances of collision. We have seen that the probability of collision is <b>1/m</b>. We can increase the value of <b>m</b> to reduce the probability of collision. But that affects the speed of the algorithm. The larger value of <b>m</b>, the slower the algorithm. Also, some languages (C, C++, Java) have a limit on the size of the integer. Hence, we can’t increase the value of <b>m</b> to a very large value.

Then how can we minimise the chances of a collision?

Note that the hash of a string depends on two parameters: <b>p</b>  and <b>m</b>.</p>

<h2>Observation</h2>
<p>If two strings produce the same hash values for a pair (p1, m1), they will produce different hashes for a different pair, (p2, m2)     .</p>

<h2>Strategy</h2>
<p>We cannot, however, nullify the chances of collision because there are infinitely many strings. But, surely, we can reduce the probability of two strings colliding.
We can reduce the probability of collision by generating a pair of hashes for a given string.</p>
