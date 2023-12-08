### RB Trees
**Question:**
Use one of following editor (only) to keyin your programs: jed,  xjed, vim, gvim, emacs, xemacs
Do not use recursion
RB-Trees are binary search trees in which each node has a non-negative integral rank (rank is 0,1,2,...) such that
	1. Rank of failure nodes is zero
	2. Rank of parent of failure node is one
	3. If "x" is any node and p(x) is parent of x, then rank(x) < rank(p(x)) < rank(x)+1
	4. If g(x) is p(p(x)), the grand parent of x, then rank(x) < rank(g(x))-1
Implement following operations on RB-trees (ranks have to be explicitly mantained).
(a) Search 10
(b) Insert 20
(c) Delete 35
(d) Try to insert 500 random numbers one by one. Then, repeatedly find, print and delete the minimum item (for 100 times) 10
