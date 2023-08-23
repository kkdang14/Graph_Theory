#include<stdio.h>
#define MAX_Vertices 500

typedef struct{
	int u,v;
}Edge;

typedef struct{
	int n,m;
	Edge edges[MAX_Vertices];
}Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
}

int adjacent(Graph *pG, int x, int y){
	int i;
	for(i=0; i< pG->m; i++)
		if((pG->edges[i].u == x && pG->edges[i].v == y) || (pG->edges[i].u == y && pG->edges[i].v == x))
			return 1;
	return 0;
}

void add_edge(Graph *pG, int x, int y){
	if(adjacent(pG, x, y) == 1 && adjacent(pG, y, x) == 1){
		return;
	}
	pG->edges[pG->m].u = x;
	pG->edges[pG->m].v = y;
	pG->m++;
}

int main(){
	Graph G;
	init_graph(&G, 4);
	add_edge(&G, 1, 3);
	add_edge(&G, 3, 2);
	add_edge(&G, 2, 4);
	add_edge(&G, 2, 2);
	add_edge(&G, 2, 2);
	
	printf("n = %d, m = %d\n", G.n, G.m);
	
	int e;
	for(e = 0; e < G.m; e++)
		printf("%d %d\n", G.edges[e].u, G.edges[e].v);
	return 0;
	return 0;
}
