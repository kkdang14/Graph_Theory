#include<stdio.h>
#define MAX_Vertices 20
#define MAX_Length 50

typedef struct{
	int data[MAX_Length];
	int size;
}List;

void makenull(List *L){
	L->size = 0;
} 

void push_back(List *L, int x){
	L->data[L->size] = x;
	L->size++;
}

int element_at(List *L, int i){
	return L->data[i-1];
}


typedef struct{
    int A[MAX_Vertices][MAX_Vertices];
    int n;
}Graph;

void init_Graph(Graph *G, int n){
	int i,j;
    G->n = n;
    for(i=1; i<=n; i++)
    	for(j =1; j<=n; j++)
    		G->A[i][j] = 0;
    
}

void add_edge(Graph *G, int x, int y){
	G->A[x][y] = 1;
	G->A[y][x] = 1;
}

int adjacent(Graph *G, int x, int y){
	return (G->A[x][y] != 0);
}

int degree(Graph *G, int x){
	int deg =0, i;
	for(i=1; i<=G->n; i++)
		if(G->A[i][x] == 1)
			deg++;
	return deg;
}

List neighbors(Graph *G, int x){
	int i;
	List L;
	makenull(&L);
	for(i=1; i<=G->n; i++){
		if(G->A[i][x] == 1)
			push_back(&L, i);
	}
	return L;
}

int main(){
    Graph G;
    freopen("dothi.txt", "r", stdin);
    int n,m; // dinh-cung
    scanf("%d%d", &n, &m);
    init_Graph(&G, n);
    int u, v, e; 
    for(e = 1; e<=m; e++){
    	scanf("%d%d", &u, &v);
    	add_edge(&G, u, v);
	}
	int i,j;
	for(i=1; i<=G.n; i++)
		printf("degree(%d) = %d\n",i, degree(&G, i));
		
	for(i=1; i<=G.n; i++){
		List L= neighbors(&G, i);
		printf("Neighbor(%d) = [", i);
		for(j=1; j<=L.size; j++)
			printf("%d ", element_at(&L, j));
		printf("]\n");
	}
	return 0;
}

