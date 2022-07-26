# Aho-Corasick Algorithm for Pattern Searching

Given an input text and an array of **k** words, arr[], find all occurrences of all words in the input text. Let **n** be the length of text and **m** be the total number characters in all words, i.e. m = length(arr[0]) + length(arr[1]) + … + length(arr[k-1]). Here k is total numbers of input words.

Example:  

Input: text = "ahishers"    
       arr[] = {"he", "she", "hers", "his"}

Output:
   Word his appears from 1 to 3
   Word he appears from 4 to 5
   Word she appears from 3 to 5
   Word hers appears from 4 to 7
If we use a linear time searching algorithm like KMP, then we need to one by one search all words in text[]. This gives us total time complexity as O(n + length(word[0]) + O(n + length(word[1]) + O(n + length(word[2]) + … O(n + length(word[k-1]). This time complexity can be written as O(n*k + m). 

Aho-Corasick Algorithm finds all words in O(n + m + z) time where z is total number of occurrences of words in text. The Aho–Corasick string matching algorithm formed the basis of the original Unix command fgrep. 

- ### Preprocessing : Build an automaton of all words in arr[] The automaton has mainly three functions:
```
Go To :   This function simply follows edges
          of Trie of all words in arr[]. It is
          represented as 2D array g[][] where
          we store next state for current state 
          and character.

Failure : This function stores all edges that are
          followed when current character doesn't
          have edge in Trie.  It is represented as
          1D array f[] where we store next state for
          current state. 

Output :  Stores indexes of all words that end at 
          current state. It is represented as 1D 
          array o[] where we store indexes
          of all matching words as a bitmap for 
          current state.
```
- ### Matching : Traverse the given text over built automaton to find all matching words.


## Preprocessing: 

- We first Build a Trie (or Keyword Tree) of all words. 
 
 ![image](https://user-images.githubusercontent.com/101459465/181090304-df6d9877-3d91-4986-908e-a1fcd174b62e.png)


- This part fills entries in goto g[][] and output o[].
- Next we extend Trie into an automaton to support linear time matching. 
 
![image](https://user-images.githubusercontent.com/101459465/181090572-224fb908-8dee-4a6f-ad47-d7017fad7be3.png)

- This part fills entries in failure f[] and output o[].


## Go to : 
We build Trie. And for all characters which don’t have an edge at root, we add an edge back to root.
## Failure : 
For a state s, we find the longest proper suffix which is a proper prefix of some pattern. This is done using Breadth First Traversal of Trie.
## Output : 
For a state s, indexes of all words ending at s are stored. These indexes are stored as bitwise map (by doing bitwise OR of values). This is also computing using Breadth First Traversal with Failure.
