#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "lexBFS.h"
#include "eep.h"
#include "chordal.h"
#include "smv.h"

void main()
{
    // int n, node1, node2;
    // printf("n :\t");
    // scanf("%d", &n);
    // struct graph *g = createGraph(n);
    // while(1){
    //     printf("### CREATING EDGES: enter like 0 1\n");
    //     printf("Enter %d to finish\n", n);

    //     scanf("%d", &node1);
    //     if(node1 == n)
    //         break;
        
    //     scanf("%d", &node2);
    //     addEdge(g, node1, node2);
    // }

    // struct graph *g = createGraph(8);
    // addEdge(g, 0, 1);
    // addEdge(g, 0, 4);
    // addEdge(g, 0, 3);
    // addEdge(g, 1, 2);
    // addEdge(g, 1, 3);
    // addEdge(g, 1, 4);
    // addEdge(g, 2, 5);
    // addEdge(g, 2, 4);
    // addEdge(g, 3, 4);
    // addEdge(g, 5, 4);
    // addEdge(g, 1, 6);
    // addEdge(g, 7, 6);

    // ESTRELA
    // struct graph *g = createGraph(5);
    // addEdge(g, 0, 1);
    // addEdge(g, 0, 2);
    // addEdge(g, 0, 3);
    // addEdge(g, 0, 4);

    struct graph *g = createGraph(10);
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 1, 4);
    addEdge(g, 3, 2);
    addEdge(g, 4, 2);
    addEdge(g, 3, 4);
    addEdge(g, 1, 2);
    addEdge(g, 6, 4);
    addEdge(g, 7, 4);
    addEdge(g, 5, 4);
    addEdge(g, 5, 6);
    addEdge(g, 5, 7);
    addEdge(g, 7, 6);
    addEdge(g, 8, 6);
    addEdge(g, 9, 6);
    addEdge(g, 9, 8);

    // struct graph *g = createGraph(4);
    // addEdge(g, 0, 1);
    // addEdge(g, 0, 3);
    // addEdge(g, 2, 1);
    // addEdge(g, 2, 3);
    // addEdge(g, 1, 3);

    // struct graph *g = createGraph(6);
    // addEdge(g, 0, 1);
    // addEdge(g, 0, 2);
    // addEdge(g, 2, 1);
    // addEdge(g, 2, 3);
    // addEdge(g, 1, 3);
    // addEdge(g, 1, 4);
    // addEdge(g, 3, 4);
    // addEdge(g, 2, 4);
    // addEdge(g, 0, 5);

    printf("GRAPH\n");
    displayGraph(g);

    isChordal(g);

    destroyGraph(g);
}
