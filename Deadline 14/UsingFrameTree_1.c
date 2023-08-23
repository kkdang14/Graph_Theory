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


int Kruskal(Graph *pG, Graph *pT) {
    qsort(pG->edges, pG->m, sizeof(Edge), cmpfunc);
    init_graph(pT, pG->n);
    int u;
    for (u = 1; u <= pG->n; u++)
        parent[u] = u; 
    int sum_w = 0;
    int k=0;
    int e;
    for ( e = 0; e < pG->m; e++) {
        int u = pG->edges[e].u;
        int v = pG->edges[e].v;
        int w = pG->edges[e].w;
        int root_u = findRoot(u); 
        int root_v = findRoot(v); 
        if (root_u != root_v) { 
    
            add_edge(pT, u, v, w);
        
            parent[root_v] = root_u;
            sum_w += w;
        }
        else{
            k += w;
        }
    }
    return k;
}


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
    
    int k = Kruskal(&G, &T); 
    printf("%d\n", k);

//    for (e = 0; e < T.m; e++)
//        printf("%d %d %d\n", T.edges[e].u, T.edges[e].v, T.edges[e].w);
    
    return 0;
}

