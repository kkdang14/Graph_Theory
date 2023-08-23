//Co huong da cung va chua khuyen 

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

int quiver=0;

void add_edge(Graph *pG, int u, int v){
    pG->A[u][v]++;
    pG->A[v][u]++;
    if(u == v){
    	pG->A[u][u] = 1;
    	pG->A[v][v] = 1;
    	quiver++;
	}
	if(quiver>=2){
		pG->A[u][u]++;
	}
    pG->m++;
}

int degree(Graph *pG, int u){
	int v, deg =0;
	for(v=1; v<=pG->n; v++)
		deg += pG->A[u][v] + pG->A[v][u];
	return deg;
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
    
    for (u = 1; u <= G.n; u++) {
    	printf("deg(%d) = %d\n", u, degree(&G, u));
    }
}
