#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "lexBFS.h"
#include "eep.h"
#include "chordal.h"

void main()
{
    // struct graph *g = createGraph(5);
    // addEdge(g, 0, 1);
    // addEdge(g, 0, 4);
    // addEdge(g, 1, 2);
    // addEdge(g, 1, 3);
    // addEdge(g, 1, 4);
    // addEdge(g, 2, 3);
    // addEdge(g, 3, 4);

    struct graph *g = createGraph(8);
    addEdge(g, 0, 1);
    addEdge(g, 0, 4);
    addEdge(g, 0, 3);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 1, 4);
    addEdge(g, 2, 5);
    //addEdge(g, 2, 4);
    addEdge(g, 3, 4);
    addEdge(g, 5, 4);
    addEdge(g, 1, 6);
    addEdge(g, 7, 6);

    printf("GRAPH\n");
    displayGraph(g);

    isChordal(g);

    destroyGraph(g);
}
