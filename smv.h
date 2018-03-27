/*smv.h*/
#ifndef SMV_H
#define SMV_H
#include <stdbool.h>
#include <string.h>
#include "graph.h"

struct smv{
	struct adjlist *smv;
	int multiplicity;
};

struct smv* smv(struct graph *g, int sigma[], int index[]){
	int q=1,j=0;
	int *position = (int *)malloc(g->n * sizeof(int));
	int *last = (int *)malloc(g->n * sizeof(int));
	struct adjlist *qSet = (struct adjlist *)malloc(g->n * sizeof(struct adjlist));
	struct smv *smvSet = (struct smv *)malloc(g->n * sizeof(struct smv));

	struct adjlist_node *firstNode = (struct adjlist_node *)malloc(sizeof(struct adjlist_node));
	firstNode->next = NULL;
	firstNode->previous = NULL;
	firstNode->vertex = sigma[g->n];
	qSet[0].head = firstNode;
	qSet[0].num_members = 1;
	
	position[sigma[g->n]] = 1;
	
	smvSet[0].smv = NULL;
	smvSet[0].multiplicity = 0;

	for(int i = 0; i < g->n; i++){
		last[i] = 0;
	}
	
	for(int i = g->n - 2; i >= 0; i--){

		int choosen_vertex = sigma[i];
		
        /* Finding monotone adjacency of vertex in sigma[i] */

        struct adjlist *monotonousAdj = (struct adjlist *)malloc(sizeof(struct adjlist));
        monotonousAdj->num_members = 0;
        monotonousAdj->head = NULL;
	    
        struct adjlist_node *adjlistPtr = g->adjlistArr[choosen_vertex].head;
        while (adjlistPtr)
        {
            if(i < index[adjlistPtr->vertex]){
                monotonousAdj->num_members++;

                struct adjlist_node *newNode = (struct adjlist_node *)malloc(sizeof(struct adjlist_node));
                newNode->vertex = adjlistPtr->vertex;
                
                if(monotonousAdj->head == NULL){
                    monotonousAdj->head = newNode;
                    newNode->next = NULL;
                    newNode->previous = NULL;
                }
                else{
                    newNode->next = monotonousAdj->head;
                    monotonousAdj->head->previous = newNode;
                    newNode->previous = NULL;
                    monotonousAdj->head = newNode;
                }
            }

            adjlistPtr = adjlistPtr->next;
        }

        printf("Monotone Adjacency list of vertex %d:\t", choosen_vertex);
        displayAdjacencyList(*monotonousAdj);
        
        if(monotonousAdj->num_members > 0){
	        /* Finding the closest vertex to sigma[i] */

	        int smallestPosition = g->n;

	        adjlistPtr = monotonousAdj->head;
	        while (adjlistPtr)
	        {
	            if(index[adjlistPtr->vertex] < smallestPosition)
	                smallestPosition = index[adjlistPtr->vertex];

	            adjlistPtr = adjlistPtr->next;
	        }

	        int closestVertex = sigma[smallestPosition];
	        printf("Closest vertex: %d\n", closestVertex);

	        /* Finished finding the closest vertex */

	        int k = position[closestVertex];

			if(monotonousAdj->num_members < qSet[k-1].num_members){
				
				q++;

				/* Adding v_i to monotonous adjacency of v_i */

				struct adjlist *newAdj = (struct adjlist *)malloc(sizeof(struct adjlist));
				memcpy(newAdj, monotonousAdj, sizeof(struct adjlist));
				
				newAdj->num_members++;

                struct adjlist_node *newNode = (struct adjlist_node *)malloc(sizeof(struct adjlist_node));
                newNode->vertex = sigma[i];
                
                newNode->next = newAdj->head;
                newAdj->head->previous = newNode;
                newNode->previous = NULL;
                newAdj->head = newNode;

                /* Finished adding v_i to monotonous adjacency of v_i */

				qSet[q-1] = *newAdj;

				printf("Creating another Maximal Click Q_%d:\t", q);
				displayAdjacencyList(*newAdj);

				position[sigma[i]] = q;
				
				int tam = monotonousAdj->num_members;
				int c = last[tam];

				bool theSame = true;

				if(smvSet[c].smv == NULL){
					theSame = false;
				}
				else{
					
					/* Creating another structure to make it linear */

					bool *auxiliar = (bool *)malloc(g->n * sizeof(bool));

			        adjlistPtr = smvSet[c].smv->head;
			        while (adjlistPtr)
			        {
			            auxiliar[adjlistPtr->vertex] = true;    
			            adjlistPtr = adjlistPtr->next;
			        }

					/* Finished creating another structure to make it linear */ 
					
					adjlistPtr = monotonousAdj->head;
			        while (adjlistPtr)
			        {
			            if(auxiliar[adjlistPtr->vertex] == false){
			                theSame = false;
			                break;
			            }
			            adjlistPtr = adjlistPtr->next;
			        }
				}

				if(!theSame){

					j++;

					struct adjlist *newSmv = (struct adjlist *)malloc(sizeof(struct adjlist));
					memcpy(newSmv, monotonousAdj, sizeof(struct adjlist));

					printf("Creating another smv S_%d:\t", j);
					displayAdjacencyList(*(newSmv));

					smvSet[j].smv = newSmv;
					smvSet[j].multiplicity = 1;

					last[tam] = j;
				}
				else{
					printf("Upgrading smv S_%d:\t", c);
					smvSet[c].multiplicity++;
				}
			}
			else{
				/* Adding v_i to Q_k */

				qSet[k-1].num_members++;

				struct adjlist_node *newNode = (struct adjlist_node *)malloc(sizeof(struct adjlist_node));
			    newNode->vertex = sigma[i];
			    newNode->next = qSet[k-1].head;
			    newNode->previous = NULL;
			    qSet[k-1].head->previous = newNode;
			    qSet[k-1].head = newNode;

				/* Finished adding v_i to Q_k */

				position[sigma[i]] = k;
				
				printf("Upgrading Maximal Click Q_%d:\t", k);
				displayAdjacencyList(qSet[k-1]);
			}
		}
	}

	return smvSet;
}


#endif