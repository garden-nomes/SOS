# Problem 9.3

> Problem: Write a program to perform a topological sort on a graph.

There are a few different algorithms one could use for a topological sort, as explained by
[wikipedia][https://en.wikipedia.org/wiki/Topological_sorting]. The algorithm the book uses
appears to be a slightly more optimized version of Kahn's algorithm. For a graph of n nodes
and m edges, it has a complexity of O(n + m), essentially linear time.

The book uses a queue to cycle through nodes of indegree 0, and I see no reason to modify that.
I have added code for computing the indegrees of nodes.

    /* assumes graph maintains the following private members
     * - vector<vector<int>> adjacencies: adjacency list
     *
     * Nodes are represented as indicies, so that an index
     * int the adjancency list can correspond to an index
     * in a node list.
     */
    void Graph::topsort()
    {
        queue<node> q;
        vector<int> sorted;
        int indegrees[adjacencies.size()];
        int counter = 0;
    
        for (vector<int> connected : adjacencies)
            for (int i : connected)
                ++indegress[i];
    
        q.makeEmpty();
        for (int i = 0; i < adjacencies.size(); ++i)
            if (indegrees[i] == 0)
                q.push_back(i);
    
        while(!q.empty()) {
            int i = q.front();
            sorted.push_back(i);
            ++counter;
    
            for (int n : adjacencies[i]) {
                --indegrees[n];
                if (indegrees[n] <= 0)
                    q.push_back(n);
            }
    
            q.pop();
        }
        if( counter != adjacencies.size() )
            throw CycleFoundException{ };
    }


# Problem 9.9

> Problem: Write a program to solve the single-source shortest-path problem.

The simplest solution I know of (and the one from the book) is Djistra's algorithm.

In order to implement it, you need to use some kind of heap to keep track of the unvisited
node with the shortest distance. The best option would probably a Fibonacci heap since that
gives us an O(1) decrease-key operation, which will be used whenever we update the distances
of adjacent nodes.

# Problem 9.15

(need to do on paper)

# Problem 9.16

Both Prim's and Kruskal's algorithms should work fine with negative weights, given that both
have checks to prevent cycles.

# Problem 9.32

(program to find Euler circuit and Euler tour in graph if one exists)

# Problem 9.46

(add pathfinding to project 2!)

# Problem 9.54

(this looks hard)

9.3, 9.9, 9.15, 9.16, 9.32, 9.46, 9.54
