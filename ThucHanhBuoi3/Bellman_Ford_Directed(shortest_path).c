#include <stdio.h>
#define INF 99999
#define MAX_N 50

typedef struct{
	int u, v;
	int w;
}Edge;

typedef struct{
	int n,m;
	Edge W[MAX_N];
}Graph;

void init_Graph(Graph *pG, int n){
	pG->n=n;
	pG->m=0;
}

int adjacent(Graph *pG, int x, int y){
	int i;
	for(i=0; i< pG->m; i++)
		if((pG->W[i].u == x && pG->W[i].v == y) )
			return 1;
	return 0;
}

void add_edge(Graph *pG, int u, int v, int w){
	if(adjacent(pG, u, v) == 1)
		return;
	pG->W[pG->m].u = u;
	pG->W[pG->m].v = v;
	pG->W[pG->m].w = w;
 	pG->m++;
}

int pi[MAX_N], p[MAX_N];

void Bellman_Ford(Graph *pG, int s){
	int i,it,j, u, v, w;
	for(i=1; i<=pG->n; i++)
		pi[i] = INF;
		
	pi[s] = 0;
	p[s] = -1;
	
	for(it=1; it < pG->n; it++){
		
		for(j=0; j< pG->m; j++){
			u = pG->W[j].u;
			v = pG->W[j].v;
			w = pG->W[j].w;
			if(pi[u] == INF)
				continue;
			if(pi[u] + w < pi[v]){
				pi[v] = pi[u] + w;
				p[v] = u;
			}		
		}
	}
	
//	// kiem tra chu trinh am
//	int nagative_circle =0;
//	
//	for(j=1; j<=pG->n; j++){
//		u = pG->W[j].u;
//		v = pG->W[j].v;
//		w = pG->W[j].w;
//		if(pi[u] == INF)
//			continue;
//		if(pi[u] + w < pi[v]){
//			nagative_circle = 1;
//			break;
//		}		
//	}
	
}


int main(){
	Graph G;
	int i,n,m,u,v,w,s,t;
	freopen("bellman_ford.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_Graph(&G, n);
	for(i=1; i<= m; i++){
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	
	scanf("%d%d", &s, &t);
	
	Bellman_Ford(&G, s);
	
//	for(u=1; u<=G.n; u++)
//		printf("pi[%d] = %d, p[%d] = %d\n", u, pi[u], u, p[u]);
	int path[MAX_N];
	int k=0, current = t;
	
	while(current != -1){
		path[k] = current;
		k++;
		current = p[current];
	}
	
	for(u = k-1; u>=0; u--)
		if(u == 0)
			printf("%d", path[u]);
		else printf("%d -> ", path[u]);
	
	return 0;
}
