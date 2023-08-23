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
		if((pG->edges[i].u == x && pG->edges[i].v == y) || (pG->edges[i].u == y && pG->edges[i].v == x))
			return 1;
	return 0;
}

int degree(Graph *pG, int x){
	int i, deg = 0;
	for(i=0; i< pG->m; i++){
		if(pG->edges[i].u == x)
			deg++;
		if(pG->edges[i].v == x)
			deg++;
	}
	return deg;
}

int main() {
    Graph G;
    int n,m,e,u,v;
    freopen("degmax.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_graph(&G, n);

    for (e = 0; e < m; e++) {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    
    for (u = 1; u <= G.n; u++){
    	printf("deg(%d) = %d\n", u, degree(&G, u));
	}
    
    int deg_max = 0, max_u, k;
    for (u = 1; u <= G.n; u++) {
    	k=degree(&G, u);
    	if(k > deg_max){
    		deg_max = k;
    		max_u = u;
    	}
	}
    		
    printf("%d %d", max_u, deg_max);
}
