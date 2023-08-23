//#include <stdio.h>
//
//#define MAXN 50
//
//typedef struct{
//	int u;
//	int v;
//	int w;
//}Edges;
//
//typedef struct{
//	int n,m;
//	Edges edges[MAXN];
//}Graph;
//
//void init_graph(Graph *pG, int n){
//	pG->n = n;
//	pG->m = 0;
//}
//
//void add_edge(Graph *pG, int u, int v, int w){
//	pG->edges[pG->m].u = u;
//	pG->edges[pG->m].v = v;
//	pG->edges[pG->m].w = w;
//	pG->m++;
//}
//
//int parent[MAXN];
//
//int findroot(int u){
//	while(parent[u] != u)
//		u =parent[u];
//	return u;
//}
//
//int kruskal(Graph *pG, Graph *pT){
//	int i,j,u,e;
//	for(i=0; i<pG->m; i++)
//		for(j=i+1; j<=pG->m; j++)
//			if(pG->edges[i].w > pG->edges[j].w){
//				Edges temp = pG->edges[i];
//				pG->edges[i] =  pG->edges[j];
//				pG->edges[j] = temp;
//			}
//	
//	init_graph(pT, pG->n);	
//		
//	for(u=1; u<=pG->n; u++)
//		parent[u] = u;
//	
//	int sum_w= 0;
//	
//	for(e=1; e<=pG->m; e++){
//		int u = pG->edges[e].u;
//		int v = pG->edges[e].v;
//		int w = pG->edges[e].w;
//		int root_u = findroot(u);
//		int root_v = findroot(v);
//		if(root_u != root_v){
//			add_edge(pT, u, v, w);
//			parent[root_v] = root_u;
//			sum_w += w;
//		}
//	}
//	
//	return sum_w;
//}
//
//
//int main(){
//	Graph G, T;
//	int i,n,m,u,v,w;
//	freopen("kruskal.txt", "r", stdin);
//	scanf("%d%d", &n, &m);
//	init_graph(&G, n);
//	for(i=0; i<m; i++){
//		scanf("%d%d%d", &u, &v, &w);
//		add_edge(&G, u, v, w);
//	}
//	
//	int sum_w = kruskal(&G, &T);
//	printf("%d\n", sum_w);
//    for(i=0; i<T.m; i++){
//		if(T.edges[i].u > T.edges[i].v){
//			int temp = T.edges[i].u;
//			T.edges[i].u = T.edges[i].v;
//			T.edges[i].v = temp;
//		}
//		printf("%d %d %d\n", T.edges[i].u, T.edges[i].v, T.edges[i].w);
//    }
//	return 0;
//}


#include <stdio.h>
#include <stdlib.h>

#define MAXM 500
#define MAXN 100

//C?u trúc d? li?u c?a 1 cung
typedef struct {
    int u, v;
    int w;
} Edge;

typedef struct {
    int n, m;
    Edge edges[MAXM];
} Graph;

void init_graph(Graph *pG, int n) {
    pG->n = n;
    pG->m = 0;
}

int min(int u, int v) {
    return u < v ? u : v;
}

int max(int u, int v) {
    return u > v ? u : v;
}


void add_edge(Graph *pG, int u, int v, int w) {
    pG->edges[pG->m].u = min(u, v);
    pG->edges[pG->m].v = max(u, v);
    pG->edges[pG->m].w = w;
    
    pG->m += 1;
}


int parent[MAXN];

/*
//Tìm g?c c?a d?nh u (d? quy)
int findRoot(int u) {
    if (parent[u] == u)
        return u;
    return findRoot(parent[u]);
}*/


//Tìm g?c c?a d?nh u (l?p)
int findRoot(int u) {
    while (parent[u] != u)
        u = parent[u];
    return u;
}

int cmpfunc(const void *a, const void *b) {
    return ((const Edge*)a)->w - ((const Edge*)b)->w;
}

//Thu?t toán Kruskal tìm cây khung nh? nh?t
int Kruskal(Graph *pG, Graph *pT) {
    //1. S?p x?p các cung c?a G theo th? t? tr?ng s? tang d?n
    qsort(pG->edges, pG->m, sizeof(Edge), cmpfunc);
    
    //2. Kh?i t?o pT không ch?a cung nào, kh?i t?o b? qu?n lý các BPLT
    init_graph(pT, pG->n);
    int u;
    for (u = 1; u <= pG->n; u++)
        parent[u] = u; //M?i d?nh u là m?t b? ph?n liên thông

    int sum_w = 0; //T?ng tr?ng s? các cung c?a cây

    //3. Duy?t qua các cung c?a G (dã s?p x?p)
    int e;
    for ( e = 0; e < pG->m; e++) {
        int u = pG->edges[e].u;
        int v = pG->edges[e].v;
        int w = pG->edges[e].w;
        int root_u = findRoot(u); //Tìm BPLT c?a u
        int root_v = findRoot(v); //Tìm BPLT c?a v
        if (root_u != root_v) { //u và v ? 2 BPLT khác nhau
            //Thêm cung (u, v; w) vào cây pT
            add_edge(pT, u, v, w);
            //G?p 2 BPLT root_u và root_v l?i
            parent[root_v] = root_u;
            sum_w += w;
        }
    }
    return sum_w;
}


//S? d?ng thu?t toán Kruskal
int main() {
    Graph G, T;
    int n, m, u, v, w, e;
	freopen("kruskal.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    for (e = 1; e <= m; e++) {
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }
    
    int sum_w = Kruskal(&G, &T); //G?i hàm Kruskal
    printf("%d\n", sum_w);

    for (e = 0; e < T.m; e++)
        printf("%d %d %d\n", T.edges[e].u, T.edges[e].v, T.edges[e].w);
    
    return 0;
}

