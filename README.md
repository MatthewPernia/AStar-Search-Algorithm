A* Search Algorithm Performance Analysis

This project compares the performance of A* Search, Dijkstra’s Algorithm,
and Greedy Best-First Search on randomly generated weighted graphs.

------------------------------------------------------------
PROJECT OVERVIEW
------------------------------------------------------------

A* Search combines:
- the actual path cost from the start node
- an estimated cost to the goal using a heuristic

The project benchmarks A* against:
- Dijkstra’s Algorithm
- Greedy Best-First Search

using multiple heuristics and varying graph conditions.

------------------------------------------------------------
ALGORITHMS IMPLEMENTED
------------------------------------------------------------

1. Dijkstra’s Algorithm
   f(n) = g(n)

   - Guarantees the optimal shortest path
   - Expands many nodes

2. Greedy Best-First Search
   f(n) = h(n)

   - Very fast
   - Does not guarantee optimality

3. A* Search
   f(n) = g(n) + h(n)

   - Balances speed and accuracy

------------------------------------------------------------
HEURISTICS TESTED
------------------------------------------------------------

1. Zero Heuristic
   h(n) = 0

   - Makes A* behave similarly to Dijkstra

2. Euclidean Heuristic

   Uses straight-line distance to the goal:

   h(n) = sqrt((x1-x2)^2 + (y1-y2)^2)

3. Aggressive Heuristic

   h(n) = 1.5 × EuclideanDistance

   - Expands fewer nodes
   - May sacrifice optimality

------------------------------------------------------------
EXPERIMENTAL SETUP
------------------------------------------------------------

The program generates random weighted graphs with:
- Randomly placed 2D nodes
- Variable graph sizes
- Variable graph densities

Graph Sizes Tested:
- 50 nodes
- 100 nodes
- 200 nodes
- 400 nodes

Graph Densities Tested:
- 0.02
- 0.05
- 0.10

Metrics Measured:
- Average path cost
- Average nodes expanded
- Total runtime

Each test configuration is averaged across multiple randomized trials.

------------------------------------------------------------
GRAPH GENERATION
------------------------------------------------------------

Each node is assigned random (x, y) coordinates.

Edge weights are calculated using:

weight = EuclideanDistance + 1

The additional +1:
- avoids zero-weight edges
- stabilizes graph behavior
- prevents unrealistic low-cost paths

------------------------------------------------------------
SAMPLE RESULTS
------------------------------------------------------------

Algorithm              Heuristic      Avg Cost     Avg Nodes Expanded
---------------------------------------------------------------------
Dijkstra               None           13.69        58.79
A*                     Zero           13.69        58.79
A*                     Euclidean      14.16        31.68
A*                     Aggressive     17.73        21.80
Greedy Best-First      Euclidean      44.54        12.50

Observations:
- Dijkstra always finds the optimal path
- A* reduces node expansion significantly
- Aggressive heuristics improve speed but reduce accuracy
- Greedy is fastest but produces poor paths

------------------------------------------------------------
PROJECT STRUCTURE
------------------------------------------------------------

.
├── main.c
├── astar.c
├── astar.h
├── Makefile
└── README.txt

------------------------------------------------------------
COMPILATION
------------------------------------------------------------

Linux / macOS:

gcc -Wall -Wextra -std=c11 main.c astar.c -o astar_project -lm

Run:

./astar_project

Using Makefile:

make
./astar_project

------------------------------------------------------------
CONCEPTS DEMONSTRATED
------------------------------------------------------------

- Graph traversal
- Pathfinding algorithms
- Heuristic search
- Admissibility
- Optimality
- Runtime analysis
- Experimental benchmarking

------------------------------------------------------------
LIMITATIONS
------------------------------------------------------------

- Uses arrays instead of a priority queue
- Random graphs only
- No visualization of paths
- Euclidean heuristic is not perfectly admissible due to modified edge weights

------------------------------------------------------------
FUTURE IMPROVEMENTS
------------------------------------------------------------

- Add binary heap priority queue
- Add real-world datasets/maps
- Visualize paths graphically
- Compare more heuristic functions
- Implement adjacency lists for better scalability
