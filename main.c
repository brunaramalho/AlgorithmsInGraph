#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "lexBFS.h"

void main()
{
    struct graph *g = createGraph(5);
    addEdge(g, 0, 1);
    addEdge(g, 0, 4);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 1, 4);
    addEdge(g, 2, 3);
    addEdge(g, 3, 4);

    printf("GRAPH\n");
    displayGraph(g);

    int *sigma = lexicographicSearch(g);

    printf("SIGMA\n");

    for(int i=0; i< g->n - 1; i++){
        printf("%d -> ", sigma[i]);
    }
    printf("%d\n", sigma[g->n - 1]);

    destroyGraph(g);
}
