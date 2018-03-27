/*strictlyChordal.h*/
#ifndef STRICTLY_CHORDAL_H
#define STRICTLY_CHORDAL_H
#include <stdbool.h>
#include "graph.h"
#include "smv.h"

bool isStrictlyChordal(struct graph *g, struct smv* smvSet){

	bool isStrictlyChordal = true;
	bool *appeared = (bool *)malloc(g->n * sizeof(int));
	int counter;

	for(counter = 0; counter < g->n; counter++)
		appeared[counter] = false;

	counter = 1;
    while(smvSet[counter].smv && isStrictlyChordal){

    	struct adjlist_node *adjlistPtr = smvSet[counter].smv->head;
	    while (adjlistPtr)
	    {
	        if(appeared[adjlistPtr->vertex] != false){
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

	return isStrictlyChordal;
}

#endif