#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "astar.h"

#define TRIALS 25

/*
    This program compares Dijkstra, Greedy Best-First Search, and A*
    on randomly generated weighted graphs.

    It varies:
        1. Graph size
        2. Graph density
        3. Search algorithm
        4. Heuristic function

    It measures:
        1. Average path cost
        2. Average nodes expanded
        3. Total runtime
*/

int main(void) {
    int sizes[] = {50, 100, 200, 400};
    double densities[] = {0.02, 0.05, 0.10};

    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    int numDensities = sizeof(densities) / sizeof(densities[0]);

    double graph[MAX_NODES][MAX_NODES];
    Point points[MAX_NODES];

    int s, d, trial;

    srand(1);

    printf("%-8s %-8s %-12s %-12s %-12s %-18s %-12s\n",
           "Size", "Density", "Algorithm", "Heuristic",
           "AvgCost", "AvgNodesExpanded", "Runtime");

    printf("-----------------------------------------------------------------------------------------\n");

    for (s = 0; s < numSizes; s++) {
        for (d = 0; d < numDensities; d++) {
            int n = sizes[s];
            double density = densities[d];

            Algorithm algorithms[] = {DIJKSTRA, GREEDY, ASTAR, ASTAR, ASTAR};
            Heuristic heuristics[] = {NONE, EUCLIDEAN, ZERO, EUCLIDEAN, AGGRESSIVE};

            int numTests = sizeof(algorithms) / sizeof(algorithms[0]);
            int test;

            for (test = 0; test < numTests; test++) {
                double totalCost = 0.0;
                double totalExpanded = 0.0;
                double totalRuntime = 0.0;

                for (trial = 0; trial < TRIALS; trial++) {
                    Result result;

                    generateGraph(n, density, graph, points);

                    result = runSearch(
                        n,
                        graph,
                        points,
                        0,
                        n - 1,
                        algorithms[test],
                        heuristics[test]
                    );

                    totalCost += result.cost;
                    totalExpanded += result.nodesExpanded;
                    totalRuntime += result.runtime;
                }

                printf("%-8d %-8.2f %-12s %-12s %-12.2f %-18.2f %-12.6f\n",
                       n,
                       density,
                       algorithmName(algorithms[test]),
                       heuristicName(heuristics[test]),
                       totalCost / TRIALS,
                       totalExpanded / TRIALS,
                       totalRuntime);
            }
        }
    }

    return 0;
}