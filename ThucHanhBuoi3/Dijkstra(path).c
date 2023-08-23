#include <stdio.h>
#define MAX_N 50
#define INF 99999


typedef struct{
	int W[MAX_N][MAX_N];
	int n,m;
}Graph;

void init_Graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	int i,j;
	for(i=1; i<=pG->n; i++)
		for(j=1; j<=pG->n; j++)
			pG->W[i][j] = -1;
	
}

void add_edge(Graph *pG, int x, int y, int w){
	pG->W[x][y] = w;
	pG->W[y][x] = w;
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
    freopen("Dijkstra_3.txt", "r", stdin);
    int n,m,j; // dinh-cung
    scanf("%d%d", &n, &m);
    init_Graph(&G, n);
    int u, v, e, z, s, t; 
    for(e = 1; e<=m; e++){
    	scanf("%d%d%d", &u, &v, &z);
    	add_edge(&G, u, v, z);
	}
	scanf("%d%d", &s, &t);
		
	Dijkstra(&G, t);
	
	for(j=1; j<=G.n; j++) 
	    printf("pi[%d] = %d, p[%d] = %d\n",j , pi[j], j, p[j]);

	
	int path[MAX_N];
	int k = 0, current = s;
	
	while(current != -1){
		path[k] = current;
		k++;
		current = p[current];
	}
	
	for(u=0; u<=k-1; u++)
		if(u == k-1)
			printf("%d",  path[u]);
		else
			printf("%d -> ",  path[u]);
	
	return 0;
}
