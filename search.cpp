#include "search.h"
#include "problem.h"
#include <limits.h>

Node* generalSearch(int initialState[N][N], int (*heuristicFunc)(int state[N][N])) {
    Node* frontier[INT_MAX];
    Node* explored[INT_MAX];
    int frontierSize, exploredSize = 0;

    Node* root = new Node(initialState, nullptr, 0, heuristicFunc(initialState));
    frontier[frontierSize] = root;
    frontierSize = frontierSize + 1;

    while (frontier > 0) {
        int minIndex = 0;

        for(int i = 1; i < frontierSize; i++) {
            if (frontier[i]->cost + frontier[i]->heuristic < frontier[minIndex]->cost + frontier[minIndex]->heuristic) {
                minIndex = i;
            }
        }

        Node* currentNode = frontier[minIndex];

        for (int i = minIndex; i < frontierSize - 1; i++) {
            frontier[i] = frontier[i + 1];
        }
        frontierSize--;

        if (isGoal(currentNode->state)) {
            return currentNode;
        }

        explored[exploredSize] = currentNode;
        exploredSize = exploredSize + 1;

        int nextStates[4][N][N];
        int nextCount;
        expand(currentNode->state, nextStates, &nextCount);

        for (int i = 0; i < nextCount; i++) {
            Node* child = new Node(nextStates[i], currentNode, currentNode->cost + 1, heuristicFunc(nextStates[i]));
            frontier[frontierSize] = child;
            frontierSize = frontierSize + 1;
        }
    }

    return nullptr;
    
}