Data Structures Chapter 10 Problems  
Noah Weiner

## Problem 10.1

> Show that the greedy algorithm to minimize the mean completion time for
> multiprocessor job scheduling works.

The textbook shows that for the single-processor case, the smallest total cost
for a job sequence is given by ordering the jobs by time, smallest to largest.
Cycling the jobs between processors ensures jobs assigned to a processor will
arrive with this same ordering. Therefore each processor is given an optimum
sequence.

## Problem 10.2

> The input is a set of jobs j1,j2,...,jN, each of which takes one time unit to
> complete. Each job ji earns di dollars if it is completed by the time limit
> ti, but no money if completed after the time limit.

> a. Give an O(N2) greedy algorithm to solve the problem.

> b. Modify your algorithm to obtain an O(N log N) time bound. (Hint: The time
> bound is due entirely to sorting the jobs by money. The rest of the algorithm
> can be implemented, using the disjoint set data structure, in o(N log N).)

```C++
#include <vector>
#include <algorithm>

struct job {
    int di, ti;

    friend bool operator<(const job & lhs, const job & rhs) {
        return lhs.di < rhs.di;
    }
};

std::vector<job> *optimal_job_ordering(std::vector<job> jobs) {
    std::vector<job> *ret = new std::vector<job>();
    int i, j, time = 0;

    /* std::sort's documentation promises an average nlogn operations */
    std::sort(jobs.begin(), jobs.end());

    while (!jobs.empty()) {
        i = jobs.size() - 1;
        x = std::max(time + 1, jobs[i].ti);

        for (j = i - 1; j >= 0; j--) {
            /* if we can do job j, and still have time to job i (and any other
             * i's we might have had before) then do job j instead */
            if (jobs[j].ti < x + 1) {
                x = jobs[j].ti + 1;
                i = j;
            }
        }

        ret.push_back(jobs[i]);
        jobs.erase(jobs.begin() + i);
        time++;
    }

    return ret;
}
```

## Problem 10.3

> A file contains only colons, spaces, newlines, commas, and digits in the
> following frequency: colon (100), space (605), newline (100), comma (705), 0
> (431), 1 (242), 2 (176), 3 (59), 4 (185), 5 (250), 6 (174), 7 (199), 8 (205),
> 9 (217). Construct the Huffman code.

```
                _______._____
               /             \
           ___.__            _._
          /      \          /   \
         .        .       _.__   ,
        / \      / \     /    \
      _._  sp   .   0   .      .
     /   \     / \     / \    / \
    .     .   1   5   4   7  8   9
   / \   / \
  .   nl 6  2
 / \
 3  :
```

## Problem 10.6

> Show that if the symbols are sorted by frequency, Huffman’s algorithm can be
> implemented in linear time.

* Start with the sorted list of symbols and an empty queue of weighted tree
  nodes.

* While the list isn't empty or the queue is larger than 1:

    * Grab the smallest element from the front of either the list or queue, twice.

    * Merge those two elements into a new tree node.

    * Enqueue the newly created tree node.

* The only tree node in the queue is the root of the Huffman tree.

## Problem 10.10

> Explain how to implement first fit and best fit in O(N log N) time.

By using a self-balancing binary search tree (such as a red-black tree) sorted
on bin weight, you can implement both algorithms in *O(n log n)* time, since
operations on the tree are *O(log n)*.

## Problem 10.11

> Show the operation of all the bin packing strategies discussed in Section
> 10.1.3 on the input 0.42, 0.25, 0.27, 0.07, 0.72, 0.86, 0.09, 0.44, 0.50,
> 0.68, 0.73, 0.31, 0.78, 0.17, 0.79, 0.37, 0.73, 0.23, 0.30.

### Next fit

```
bin 1   bin 2   bin 3   bin 4   bin 5   bin 6
0.42    0.07    0.86    0.44    0.68    0.73
0.25    0.72    0.09    0.50
0.27

bin 7   bin 8   bin 9   bin 10  bin 11  bin 12
0.31    0.78    0.79    0.37    0.73    0.30
        0.17                    0.23
```

### First fit

```
bin 1   bin 2   bin 3   bin 4   bin 5   bin 6
0.42    0.07    0.86    0.44    0.68    0.73
0.25    0.72            0.50    0.31    0.17
0.27    0.09

bin 7   bin 8   bin 9   bin 10  bin 11
0.78    0.79    0.37    0.73    0.30
                0.23
```

### Best fit

```
bin 1   bin 2   bin 3   bin 4   bin 5   bin 6
 0.42   0.07    0.86    0.44    0.68    0.73
 0.25   0.72    0.09    0.50    0.31
 0.27   0.17

bin 7   bin 8   bin 9   bin 10
0.78    0.79    0.37    0.73
                0.30    0.23
```