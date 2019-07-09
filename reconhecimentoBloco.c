#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "lexBFS.h"
#include "eep.h"
#include "smv.h"

bool isBlock(struct graph *g){
	struct output result = lexBFS(g);

    struct graph *g_representation = createGraph(g->n);
    
    bool isChordal = eep(g, result.sigma, result.index, g_representation);

    if(isChordal){
        struct smv *smvSet = smv(g, result.sigma, result.index);

        int counter = 1;
        bool block = true;
        while(smvSet[counter].smv && block){
            int vertexCounter = 0;
            struct adjlist_node *adjlistPtr = smvSet[counter].smv->head;
            
            while (adjlistPtr)
            {
                vertexCounter++;

                if(vertexCounter>1){
                    block = false;
                    break;
                }

                adjlistPtr = adjlistPtr->next;
            }

            counter++;
        }

        return block;
    }
    else
        return false;
}

void main(int argc, char *argv[]){
    struct graph *g = createGraph(atoi(argv[1]));
    
    for(int i = 1; i <= (argc-2)/2; i++) {
        addSingleEdge(g, atoi(argv[2*i]), atoi(argv[2*i+1]));
    }

    // displayGraph(g);

    if(isBlock(g))
        printf("3");
    else
        printf("4");
}