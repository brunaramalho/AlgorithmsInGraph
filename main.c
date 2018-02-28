#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "lexBFS.h"

void main()
{
    struct graph *G = createGraph(5);
    addEdge(G, 0, 1);
    addEdge(G, 0, 4);
    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    addEdge(G, 1, 4);
    addEdge(G, 2, 3);
    addEdge(G, 3, 4);

    printf("\nGRAPH");
    displayGraph(G);
    destroyGraph(G);
}
