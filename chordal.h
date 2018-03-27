/*chordal.h*/
#ifndef CHORDAL_H
#define CHORDAL_H
#include <stdbool.h>
#include "graph.h"
#include "lexBFS.h"
#include "eep.h"
#include "smv.h"
#include "strictlyChordal.h"

bool isChordal(struct graph *g){
	
	struct output result = lexBFS(g);

    printf("SIGMA\n");

    for(int i=0; i< g->n - 1; i++){
        printf("%d -> ", result.sigma[i]);
    }
    printf("%d\n", result.sigma[g->n - 1]);

    printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");

    printf("EEP TEST\n");

    struct graph *g_representation = createGraph(g->n);

	if(eep(g, result.sigma, result.index,g_representation)){
        printf("\nIt's a chordal graph!\n");

        printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");

        printf("Representation by Monotone Adjacency Sets\n");

        displayRepresentationGraph(g_representation, result.sigma);

        printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");

        struct smv *smvSet = smv(g, result.sigma, result.index);

        int counter = 1;
        while(smvSet[counter].smv){
            printf("\nS_%d with multiplicity %d:\t", counter, smvSet[counter].multiplicity);
            displayAdjacencyList(*(smvSet[counter].smv));
            counter++;
        }
        printf("\n");

        isStrictlyChordal(g, smvSet);
    }
    else
        printf("\nIt's not a chordal graph!\n");
}


#endif