#include <stdio.h>

#define MAXN 50

typedef struct{
	int u;
	int v;
	int w;
}Edges;

typedef struct{
	int n,m;
	Edges edges[MAXN];
}Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
}

void add_edge(Graph *pG, int u, int v, int w){
	pG->edges[pG->m].u = u;
	pG->edges[pG->m].v = v;
	pG->edges[pG->m].w = w;
	pG->m++;
}

int parent[MAXN];

int findroot(int u){
	while(parent[u] != u)
		u =parent[u];
	return u;
}

int kruskal(Graph *pG, Graph *pT){
	int i,j,u,e;
	for(i=0; i<pG->m; i++)
		for(j=i+1; j<=pG->m; j++)
			if(pG->edges[i].w > pG->edges[j].w){
				Edges temp = pG->edges[i];
				pG->edges[i] =  pG->edges[j];
				pG->edges[j] = temp;
			}
	
	init_graph(pT, pG->n);	
		
	for(u=1; u<=pG->n; u++)
		parent[u] = u;
	
	int sum_w= 0;
	
	for(e=1; e<=pG->m; e++){
		int u = pG->edges[e].u;
		int v = pG->edges[e].v;
		int w = pG->edges[e].w;
		int root_u = findroot(u);
		int root_v = findroot(v);
		if(root_u != root_v){
			add_edge(pT, u, v, w);
			parent[root_v] = root_u;
			sum_w += w;
		}
	}
	
	return sum_w;
}


int main(){
	Graph G, T;
	int i,n,m,u,v,w;
// 	freopen("kruskal.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(i=0; i<m; i++){
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	
	int sum_w = kruskal(&G, &T);
	printf("%d\n", sum_w);
	return 0;
}
