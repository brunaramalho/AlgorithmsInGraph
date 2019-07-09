#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "lexBFS.h"
#include "eep.h"
#include "smv.h"

bool isChordal(struct graph *g){
	struct output result = lexBFS(g);
    
    struct graph *g_representation = createGraph(g->n);
    
    return eep(g, result.sigma, result.index, g_representation);
}

void main(int argc, char *argv[]){
    struct graph *g = createGraph(atoi(argv[1]));
    
    for(int i = 1; i <= (argc-2)/2; i++) {
        addSingleEdge(g, atoi(argv[2*i]), atoi(argv[2*i+1]));
    }

    // displayGraph(g);

    if(isChordal(g))
        printf("1");
    else
        printf("2");
}