#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "astar.h"

/*
    Returns a random double between 0 and 1.
*/
static double randomDouble(void) {
    return (double)rand() / RAND_MAX;
}

/*
    Calculates Euclidean distance between two points.
    This is used both for edge weights and for the A* heuristic.
*/
static double distance(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

/*
    Heuristic function used by A* and Greedy Best-First Search.

    ZERO:
        Always returns 0, so A* behaves like Dijkstra.

    EUCLIDEAN:
        Uses straight-line distance from the current node to the goal.

    AGGRESSIVE:
        Uses a larger version of Euclidean distance.
        This can expand fewer nodes, but may produce a worse path.
*/
static double heuristicValue(Point points[MAX_NODES], int current, int goal, Heuristic heuristic) {
    if (heuristic == NONE || heuristic == ZERO) {
        return 0.0;
    }

    if (heuristic == EUCLIDEAN) {
        return distance(points[current], points[goal]);
    }

    if (heuristic == AGGRESSIVE) {
        return 1.5 * distance(points[current], points[goal]);
    }

    return 0.0;
}

/*
    Creates a random undirected weighted graph.

    n:
        Number of vertices.

    density:
        Probability that an edge exists between two nodes.

    The graph is made connected by first adding a simple chain:
        0 -- 1 -- 2 -- 3 -- ... -- n-1

    Then extra random edges are added based on density.
*/
void generateGraph(int n, double density, double graph[MAX_NODES][MAX_NODES], Point points[MAX_NODES]) {
    int i, j;

    for (i = 0; i < n; i++) {
        points[i].x = randomDouble() * 1000.0;
        points[i].y = randomDouble() * 1000.0;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            graph[i][j] = 0.0;
        }
    }

    /*
        Add chain edges so there is always at least one path
        from the start node to the goal node.
    */
    for (i = 0; i < n - 1; i++) {
        double w = distance(points[i], points[i + 1]) + 1.0;
        graph[i][i + 1] = w;
        graph[i + 1][i] = w;
    }

    /*
        Add random edges based on density.
    */
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (graph[i][j] == 0.0 && randomDouble() < density) {
                double w = distance(points[i], points[j]) + 1.0;
                graph[i][j] = w;
                graph[j][i] = w;
            }
        }
    }
}

/*
    Finds the unvisited node with the smallest priority value.
    This is a simple replacement for a priority queue.

    It is slower than a heap, but much easier to understand
    and works fine for this project.
*/
static int findBestNode(int n, int visited[MAX_NODES], double priority[MAX_NODES]) {
    int i;
    int best = -1;
    double bestValue = INF;

    for (i = 0; i < n; i++) {
        if (!visited[i] && priority[i] < bestValue) {
            bestValue = priority[i];
            best = i;
        }
    }

    return best;
}

/*
    Runs one of the three search algorithms:

    DIJKSTRA:
        priority = distance from start

    GREEDY:
        priority = heuristic distance to goal

    ASTAR:
        priority = distance from start + heuristic distance to goal
*/
Result runSearch(int n, double graph[MAX_NODES][MAX_NODES], Point points[MAX_NODES],
                 int start, int goal, Algorithm algorithm, Heuristic heuristic) {
    int i;
    int visited[MAX_NODES];
    double cost[MAX_NODES];
    double priority[MAX_NODES];

    Result result;
    clock_t begin, end;

    result.nodesExpanded = 0;
    result.cost = INF;
    result.runtime = 0.0;

    for (i = 0; i < n; i++) {
        visited[i] = 0;
        cost[i] = INF;
        priority[i] = INF;
    }

    cost[start] = 0.0;

    if (algorithm == GREEDY) {
        priority[start] = heuristicValue(points, start, goal, heuristic);
    } else if (algorithm == ASTAR) {
        priority[start] = cost[start] + heuristicValue(points, start, goal, heuristic);
    } else {
        priority[start] = cost[start];
    }

    begin = clock();

    while (1) {
        int current = findBestNode(n, visited, priority);

        if (current == -1) {
            break;
        }

        visited[current] = 1;
        result.nodesExpanded++;

        if (current == goal) {
            result.cost = cost[goal];
            break;
        }

        for (i = 0; i < n; i++) {
            if (graph[current][i] > 0.0 && !visited[i]) {
                double newCost = cost[current] + graph[current][i];

                if (newCost < cost[i]) {
                    cost[i] = newCost;

                    if (algorithm == DIJKSTRA) {
                        priority[i] = cost[i];
                    } else if (algorithm == GREEDY) {
                        priority[i] = heuristicValue(points, i, goal, heuristic);
                    } else {
                        priority[i] = cost[i] + heuristicValue(points, i, goal, heuristic);
                    }
                }
            }
        }
    }

    end = clock();

    result.runtime = (double)(end - begin) / CLOCKS_PER_SEC;
    return result;
}

const char *algorithmName(Algorithm algorithm) {
    if (algorithm == DIJKSTRA) {
        return "Dijkstra";
    }

    if (algorithm == GREEDY) {
        return "Greedy";
    }

    if (algorithm == ASTAR) {
        return "A*";
    }

    return "Unknown";
}

const char *heuristicName(Heuristic heuristic) {
    if (heuristic == NONE) {
        return "None";
    }

    if (heuristic == ZERO) {
        return "Zero";
    }

    if (heuristic == EUCLIDEAN) {
        return "Euclidean";
    }

    if (heuristic == AGGRESSIVE) {
        return "Aggressive";
    }

    return "Unknown";
}