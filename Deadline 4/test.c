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
    pG->A[u][u] = 1;
    pG->A[v][v] = 1;
    pG->m++;
}

int degree(Graph *pG, int u){
	int v, deg =0;
	for(v=1; v<=pG->n; v++)
		deg += pG->A[u][v];
	return deg + pG->A[u][u];
}

void neighbors(Graph *pG, int u){
	int v,i;
	for(v=1; v<=pG->n; v++)
		if(pG->A[u][v] ==1)
			printf("%d ", v);
	printf("\n");
}

int main() {
    Graph G;
    int n,m,e,u,v;
    int a[MAX_N][MAX_N];
    scanf("%d%d", &n);

    for(e = 1; e <= n; e++){
        for(u=1; u<= n; u++)
        	scanf("%d ", &G.A[e][u]);
    }
    
    for(e = 1; e <= n; e++)
        for(u=1; u<= n; u++)
    		if(G.A[u][v] >0)
    			for(v=1; v<=G.A[u][v]; v++){
    				add_edge(&G, u, v);
    				add_edge(&G, v, u);
    			} 
    			
    for(u=1; u<=G.m; u++)
    	
	return 0;
}
