#include <stdio.h>
#define INF 99999
#define MAX_N 50

typedef struct{
	int n,m;
	int W[MAX_N][MAX_N];
}Graph;

void init_Graph(Graph *pG, int n){
	int i,j;	
	pG->n=n;
	pG->m = 0;
	for(i=1; i<=pG->n; i++)
		for(j=1; j<=pG->n; j++)
			pG->W[i][j] = -1;
}

void add_edge(Graph *pG, int x, int y, int w){
	pG->W[x][y] = w;
	pG->m++;
}


int mark[MAX_N];
int pi[MAX_N], p[MAX_N];

void Dijkstra(Graph *pG, int x){
	int u, it;
	for(u=1; u<=pG->n; u++){
		pi[u] = INF;
		mark[u] = 0;
	}
	
	pi[x] = 0;
	p[x] = -1;
	
	for(it =1; it<pG->n; it++){
		
		int k, min_pi = INF;
		for(k = 1; k<=pG->n; k++){
			if(mark[k] == 0 && pi[k] < min_pi){
				min_pi = pi[k];
				u = k;
			}
		}
			
		mark[u] = 1;
		
		int v;
		for(v=1; v<=pG->n; v++){
			if(mark[v]== 0 && pG->W[u][v] != -1)
				if(pi[u] + pG->W[u][v] < pi[v]){
					pi[v] = pi[u] + pG->W[u][v];
					p[v] = u; 
				}
		}		
	}
}



int main(){
	Graph G;
	int i,n,m,w;
	freopen("Dijkstra_4.txt", "r", stdin);
	scanf("%d%d", &m, &n);
	init_Graph(&G, n*m);
	
	for(i=1; i<=n*m; i++){
		scanf("%d", &w);
		if(i + n <= n*m) // down
			add_edge(&G, i+n, i, w);
		if(i > n) // up
			add_edge(&G, i-n, i, w);
		if(i % n !=0) // right
			add_edge(&G, i+1, i, w);
		if(i % n !=1) //left
			add_edge(&G, i-1, i, w);
	}
	
	Dijkstra(&G, 1);
	
	printf("%d\n", pi[n*m]);
}
