# Stable Marriage Problem

The Stable Marriage Problem states that given N men and N women, where each person has ranked all members of the opposite sex in order of preference, marry the men and women together such that there are no two people of opposite sex who would both rather have each other than their current partners. If there are no such people, all the marriages are “stable”.

Consider the following example.
Let there be two men m1 and m2 and two women w1 and w2.
Let m1’s list of preferences be {w1, w2} 
Let m2’s list of preferences be {w1, w2} 
Let w1’s list of preferences be {m1, m2} 
Let w2’s list of preferences be {m1, m2}

The matching { {m1, w2}, {w1, m2} } is not stable because m1 and w1 would prefer each other over their assigned partners.
The matching {m1, w1} and {m2, w2} is stable because there are no two people of opposite sex that would prefer each other
over their assigned partners.

It is always possible to form stable marriages from lists of preferences (See references for proof). Following is Gale–Shapley algorithm to find a stable matching: 
The idea is to iterate through all free men while there is any free man available. Every free man goes to all women in his preference list according to the order. For every woman he goes to, he checks if the woman is free, if yes, they both become engaged. If the woman is not free, then the woman chooses either says no to him or dumps her current engagement according to her preference list. So an engagement done once can be broken if a woman gets better option. Time Complexity of Gale-Shapley Algorithm is O(n2). 

Initialize all men and women to free
while there exist a free man m who still has a woman w to propose to 
{
    w = m's highest ranked such woman to whom he has not yet proposed
    if w is free
       (m, w) become engaged
    else some pair (m', w) already exists
       if w prefers m to m'
          (m, w) become engaged
           m' becomes free
       else
          (m', w) remain engaged    
}
Input & Output: Input is a 2D matrix of size (2*N)*N where N is number of women or men. Rows from 0 to N-1 represent preference lists of men and rows from N to 2*N – 1 represent preference lists of women. So men are numbered from 0 to N-1 and women are numbered from N to 2*N – 1. The output is list of married pairs. 
