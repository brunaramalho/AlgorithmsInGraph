/*chordal.h*/
#ifndef CHORDAL_H
#define CHORDAL_H
#include <stdbool.h>
#include "graph.h"
#include "lexBFS.h"
#include "eep.h"

bool isChordal(struct graph *g){
	
	struct output result = lexBFS(g);

    printf("SIGMA\n");

    for(int i=0; i< g->n - 1; i++){
        printf("%d -> ", result.sigma[i]);
    }
    printf("%d\n", result.sigma[g->n - 1]);

    printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");

    printf("EEP TEST\n");

	if(eep(g, result.sigma, result.index))
        printf("\nIt's a chordal graph!\n");
    else
        printf("\nIt's not a chordal graph!\n");
}


#endif