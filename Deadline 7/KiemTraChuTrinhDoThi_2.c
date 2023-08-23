#include <stdio.h>
#define WHITE 0
#define GREY 1
#define BLACK 2
#define MAX_N 100

typedef struct {
    int n, m;
    int A[MAX_N][MAX_N];
} Graph;

void init_graph(Graph *pG, int n) {
    pG->n = n;
    pG->m = 0;
    int u,v;
    for (u = 1 ; u <= n; u++)
        for (v = 1 ; v <= n; v++)
            pG->A[u][v] = 0;
}

void add_edge(Graph *pG, int u, int v) {
    pG->A[u][v] += 1;
    if (u != v)
        pG->A[v][u] += 1;
    pG->m++;
}

int adjacent(Graph *pG, int u, int v) {
    return pG->A[u][v] != 0;
}

int color[MAX_N], has_circle;

void DFS(Graph *pG, int u) {
	int v;
	//printf("Duyet %d\n", u);	
	color[u] = GREY; 		
	
	for (v = 1; v <= pG->n; v++)
		if (adjacent(pG, u, v)){
			if(color[v] == WHITE)
				DFS(pG, v); 
			else if(color[v] == GREY)			    
				has_circle = 1;
		}	
	color[u] = BLACK;
}

//int connected(Graph *pG) {
//	for (int u = 1; u <= pG->n; u++)
//		mark[u] = 0;
//	DFS(pG, 1);
//	for (int u = 1; u <= pG->n; u++)
//		if (mark[u] == 0)
//			return 0; 	
//	return 1;		
//}


int main() {
	Graph G;
	freopen("DFS.txt", "r", stdin);
	int n, m, u, v, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (e = 0; e < m; e++) {
	    scanf("%d%d", &u, &v);
	    add_edge(&G, u, v);
	}

	for (u = 1; u <= G.n; u++) {
		color[u] = WHITE;
	}
	has_circle =0;
	for (u = 1; u <= G.n; u++)
		if(color[u]==WHITE){
			DFS(&G, u);	 	
		}
	
//	printf((has_circle==1) ? "YES" : "NO");

	if(has_circle == 1)
		printf("CIRCLED");
	else
		printf("NO CIRCLED");
		
    return 0;
}


