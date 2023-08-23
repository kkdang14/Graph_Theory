#include <stdio.h>

#define NO_EDGE 0
#define MAXN 50
#define INF 99999

typedef struct{
	int n, m;
	int A[MAXN][MAXN];
}Graph;

void init_graph(Graph *pG, int n){
	int i,j;
	pG->n = n;
	pG->m = 0;
	for(i=1; i<=pG->n; i++)
		for(j=1; j<=pG->n; j++)
			pG->A[i][j] = NO_EDGE;
}

void add_edge(Graph *pG, int u, int v, int w){
	pG->A[u][v] = w;
	pG->A[v][u] = w;
	pG->m++;
}

int p[MAXN], pi[MAXN], mark[MAXN];

int Prim(Graph *pG, Graph *pT, int s){
	int i,j,it,u,v,e;
	for(i=1; i<=pG->n; i++){
		p[i] = -1;
		pi[i] = INF;
		mark[i] = 0;
	}
	
	pi[s] = 0;
	
	for(it=1; it<pG->n; it++){
		int min_dist = INF;
		for(j=1; j<=pG->n; j++)
			if(mark[j] == 0 && pi[j] < min_dist){
				min_dist = pi[j];
				u = j;	
			}
		
		mark[u] = 1;	
		for(v=1; v<=pG->n; v++)
			if(pG->A[u][v] != NO_EDGE)
				if(mark[v] == 0 && pi[v] > pG->A[u][v]){
					pi[v] = pG->A[u][v];
					p[v] = u;
				}
	}
	
	init_graph(pT, pG->n);
	int sum_w = 0;
	for(e=1; e<=pG->n; e++)
		if(p[e] != -1){
			int w = pG->A[p[e]][e];
			add_edge(pT, p[e], e, w);
			sum_w += w;
		}
	return sum_w;
}

int main(){
	Graph G, T;
	int i,j,n,m,u,v,w;
 	freopen("prim.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(i=0; i<m; i++){
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	int sum_w;
	for(u=1; u<=G.n; u++)
		sum_w = Prim(&G, &T, u);
	printf("%d\n", sum_w);
    for(i=1; i<=T.m; i++){
		printf("%d %d %d\n", i, i+1, T.A[i][i+1]);
    }
	return 0;
}



