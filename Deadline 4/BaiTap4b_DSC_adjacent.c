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

void add_edge(Graph *pG, int x, int y){
	pG->edges[pG->m].u = x;
	pG->edges[pG->m].v = y;
	pG->m++;
}

int adjacent(Graph *pG, int x, int y){
	int i;
	for(i=0; i< pG->m; i++)
		if(pG->edges[i].u == x && pG->edges[i].v == y)
			return 1;
	return 0;
}

int main(){
	Graph G;
	init_graph(&G, 3);
add_edge(&G, 1, 3);
add_edge(&G, 2, 3);
add_edge(&G, 2, 2);
	
	int e;
	for(e = 0; e < G.m; e++){
		if(adjacent(&G, G.edges[e].u, G.edges[e].v) ==0)
			printf("%d KHONG ke voi %d.\n", G.edges[e].u, G.edges[e].v);
		if(adjacent(&G, G.edges[e].v, G.edges[e].u) ==0)
			printf("%d KHONG ke voi %d.\n", G.edges[e].u, G.edges[e].v);
		if(adjacent(&G, G.edges[e].u, G.edges[e].v) ==1)
			printf("%d ke voi %d.\n", G.edges[e].u, G.edges[e].v);
		if(adjacent(&G, G.edges[e].v, G.edges[e].u) ==1)
			 printf("%d ke voi %d.\n", G.edges[e].v, G.edges[e].u);
	}
	return 0;
}
