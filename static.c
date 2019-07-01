#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "staticBlock.h"

void main(int argc, char *argv[]){
    int n = atoi(argv[1]);

    struct graph *g = createStatic(n);

    displayGraph(g);

    destroyGraph(g);
}