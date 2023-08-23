#include <stdio.h>
#define MAX_N 100

typedef struct {
	int n, m;
	int A[MAX_N][MAX_N];
} Graph;

void init_graph(Graph *pG, int n){
    int i,j;
    pG->n = n;
    pG->m = 0;
    for(i=1; i<=n; i++){
        for(j=1; j<=n; j++)
            pG->A[i][j] = 0;
    }
}

void add_edge(Graph *pG, int u, int v){
    pG->A[u][v] = 1;
    pG->A[v][u] = 1;
    pG->m++;
}

int main() {
    Graph G;
    int n,m,e,u,v;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);

    for (e = 0; e < m; e++) {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    
	printf("Ma tran ke: \n");
    for (u = 1; u <= G.n; u++) {
        for (v = 1; v <= G.n; v++)
            printf("%d ", G.A[u][v]);
        printf("\n");	
    }
	if(G.m > 5)
		printf("So cung: %d", G.m);	
    return 0;
}
