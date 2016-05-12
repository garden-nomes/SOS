Data Structures Chapter 9 Problems
Noah Weiner

## Problem 10.1

> Show that the greedy algorithm to minimize the mean completion time for
> multiprocessor job scheduling works.

## Problem 10.2

> The input is a set of jobs j1,j2,...,jN, each of which takes one time unit to
> complete. Each job ji earns di dollars if it is completed by the time limit
> ti, but no money if completed after the time limit.

> a. Give an O(N2) greedy algorithm to solve the problem.

> b. Modify your algorithm to obtain an O(N log N) time bound. (Hint: The time
> bound is due entirely to sorting the jobs by money. The rest of the algorithm
> can be implemented, using the disjoint set data structure, in o(N log N).)

## Problem 10.3

> A file contains only colons, spaces, newlines, commas, and digits in the
> following frequency: colon (100), space (605), newline (100), comma (705), 0
> (431), 1 (242), 2 (176), 3 (59), 4 (185), 5 (250), 6 (174), 7 (199), 8 (205),
> 9 (217). Construct the Huffman code.

## Problem 10.6

> Show that if the symbols are sorted by frequency, Huffman’s algorithm can be
> implemented in linear time.

## Problem 10.10

> Explain how to implement first fit and best fit in O(N log N) time.

## Problem 10.11

> Show the operation of all the bin packing strategies discussed in Section
> 10.1.3 on the input 0.42, 0.25, 0.27, 0.07, 0.72, 0.86, 0.09, 0.44, 0.50,
> 0.68, 0.73, 0.31, 0.78, 0.17, 0.79, 0.37, 0.73, 0.23, 0.30.