#include<stdio.h>
#define INF 99999
#define NO_EDGE -1
#define MAX_N 50

typedef struct{
	int n,m;
	int W[MAX_N][MAX_N];
}Graph;

void init_Graph(Graph *pG, int n){
	int i,j;
	pG->n = n;
	pG->m = 0;
	for(i=1; i<=pG->n; i++)
		for(j=1; j<=pG->n; j++)
			pG->W[i][j] = NO_EDGE;
}

void add_edge(Graph *pG, int u, int v, int w){
	pG->W[u][v] = w;
//	pG->W[v][u] = w;
//	pG->m++;
}

int mark[MAX_N], pi[MAX_N], p[MAX_N];

void NguuLangChucNu(Graph *pG, int x){
	int u,v,it,j;
	for(u=1; u<=pG->n; u++){
		pi[u] =  INF;
		mark[u] = 0;
	}
	
	pi[x] = 0;
	p[x] = -1;
	
	for(it=1; it<pG->n; it++){
		
		int min_pi = INF;
		for(j=1; j<=pG->n; j++)
			if(mark[j]==0 && pi[j] < min_pi){
				min_pi = pi[j];
				u = j;
			}
		
		mark[u] = 1;
		
		for(v=1; v<=pG->n; v++){
			if(mark[v]==0 && pG->W[u][v] !=NO_EDGE){
				if(pi[u] + pG->W[u][v] < pi[v]){
					pi[v] = pi[u] +pG->W[u][v];
					p[v] = u;
				}
			}
		}
	}
}

int main(){
	Graph G;
	int n,m,u,v,q,i;
	freopen("OKieu.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_Graph(&G, n);

	for(i=1; i<= m; i++){
		scanf("%d%d%d", &u, &v, &q);
		add_edge(&G, u, v, q);
	}
	
	NguuLangChucNu(&G, 1);
	
	if(pi[n] == INF)
		printf("-1");
	else
		printf("%d", pi[n]);
	    
	return 0;
}

