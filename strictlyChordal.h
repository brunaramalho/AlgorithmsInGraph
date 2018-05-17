/*strictlyChordal.h*/
#ifndef STRICTLY_CHORDAL_H
#define STRICTLY_CHORDAL_H
#include <stdbool.h>
#include "graph.h"
#include "smv.h"

struct result{
	bool isStrictlyChordal;
	int vertexCounter;
};

struct result isStrictlyChordal(struct graph *g, struct smv* smvSet){

	bool isStrictlyChordal = true;
	bool *appeared = (bool *)malloc(g->n * sizeof(int));
	int counter;

	for(counter = 0; counter < g->n; counter++)
		appeared[counter] = false;

	counter = 1;
	int vertexCounter = 0; // number of vertices in smvs for strictly interval algorithm
    while(smvSet[counter].smv && isStrictlyChordal){

    	struct adjlist_node *adjlistPtr = smvSet[counter].smv->head;
	    while (adjlistPtr)
	    {
			vertexCounter++;

	        if(appeared[adjlistPtr->vertex]){
	        	isStrictlyChordal = false;
	        	break;
	        }
	        else
	        	appeared[adjlistPtr->vertex] = true;

	        adjlistPtr = adjlistPtr->next;
	    }

        counter++;
    }

    printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");

    if(isStrictlyChordal)
    	printf("\nIt's a strictly chordal graph!\n");
    else
    	printf("\nIt's not a strictly chordal graph!\n");

	struct result output;
	output.isStrictlyChordal = isStrictlyChordal;
	output.vertexCounter = vertexCounter;

    return output;
}

#endif