/*strictlyInterval.h*/
#ifndef STRICTLY_INTERVAL_H
#define STRICTLY_INTERVAL_H
#include <stdbool.h>
#include "graph.h"
#include "smv.h"
#include "lexBFS.h"

struct graph* derivedGraph(struct graph *g, struct smv* smvSet, int vertexCounter){
    
    struct graph *derived = createGraph(vertexCounter);
    
    int mapping[g->n]; // matrix for the new index value in derived graph foreach vertex
    
    bool inSmv[g->n];
    for(int i=0; i<g->n; i++)
        inSmv[i] = false;

    int vertexIndex = 0;
    int counter = 1;

    while(smvSet[counter].smv){

    	struct adjlist_node *adjlistPtr = smvSet[counter].smv->head;
	    while (adjlistPtr)
	    {
            mapping[adjlistPtr->vertex] = vertexIndex;

            struct adjlist_node *adjnodePtr = g->adjlistArr[adjlistPtr->vertex].head;
            while (adjnodePtr)
            {
                if(inSmv[adjnodePtr->vertex]){
                    addEdge(derived, vertexIndex, mapping[adjnodePtr->vertex]);
                }

                adjnodePtr = adjnodePtr->next;
            }
            inSmv[adjlistPtr->vertex] = true;            

	        adjlistPtr = adjlistPtr->next;
            vertexIndex++;
	    }
        counter++;
    }

    return derived;
}

bool isStrictlyInterval(struct graph *g, struct smv* smvSet, int vertexCounter){
  
    printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");

	bool isStrictlyInterval = true;

    struct graph *derived = derivedGraph(g, smvSet, vertexCounter);

    displayGraph(derived);

    struct output result = lexBFS(derived);
    struct smv *smvSetDerived = smv(derived, result.sigma, result.index);

    int counterBefore = 0;
    while(smvSet[counterBefore+1].smv){
        counterBefore++;
    }
	int counterAfter = 0;
    while(smvSetDerived[counterAfter+1].smv){
        counterAfter++;
    }

    printf("\nNumber of smvs before: %d\n", counterBefore);
    printf("Number of smvs after: %d\n", counterAfter);

    if(counterBefore-counterAfter > 2)
        isStrictlyInterval = false;
      
    if(isStrictlyInterval)
    	printf("\nIt's a strictly interval graph!\n");
    else
    	printf("\nIt's not a strictly interval graph!\n");

	return isStrictlyInterval;
}

#endif