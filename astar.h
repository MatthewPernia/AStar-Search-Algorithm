#ifndef ASTAR_H
#define ASTAR_H

#define MAX_NODES 500
#define INF 1000000000.0

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    int nodesExpanded;
    double cost;
    double runtime;
} Result;

typedef enum {
    DIJKSTRA,
    GREEDY,
    ASTAR
} Algorithm;

typedef enum {
    NONE,
    ZERO,
    EUCLIDEAN,
    AGGRESSIVE
} Heuristic;

void generateGraph(int n, double density, double graph[MAX_NODES][MAX_NODES], Point points[MAX_NODES]);
Result runSearch(int n, double graph[MAX_NODES][MAX_NODES], Point points[MAX_NODES],
                 int start, int goal, Algorithm algorithm, Heuristic heuristic);

const char *algorithmName(Algorithm algorithm);
const char *heuristicName(Heuristic heuristic);

#endif