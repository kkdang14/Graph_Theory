#include<stdio.h>
#define MAX_Vertices 20
#define MAX_Length 50
#define MAX_Element 50

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
    int data[MAX_Length];
    int Front, Rear;
}Queue;

void makenullQueue(Queue *Q){
    Q->Front =0;
    Q->Rear =-1;
}

int emptyQueue(Queue *Q){
	return Q->Front > Q->Rear;
}

void push_queue(Queue *Q, int x){
	Q->Rear++;
	Q->data[Q->Rear] = x;
}

int top(Queue *Q){
	return Q->data[Q->Front];
}

void pop(Queue *Q){
	Q->Front++;
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

void BFS(Graph *G, int x){
	Queue Q;
	makenullQueue(&Q);
	push_queue(&Q, x);
	int i,j, mark[MAX_Vertices];
	for(i=1; i<=G->n; i++)
		mark[i] = 0;
	while(!emptyQueue(&Q)){
		int u = top(&Q);
		pop(&Q);
		if(mark[u] == 1)
			continue;
		printf("%d\n", u);
		mark[u] = 1;
		List L = neighbors(G, u);
		for(j=1; j<=L.size; j++){
			int v = element_at(&L, j);
			if(mark[v] == 0)
				push_queue(&Q, v);
		}
	}
}
int main(){
    Graph G;
    freopen("BFS.txt", "r", stdin);
    int n,m; // dinh-cung
    scanf("%d%d", &n, &m);
    init_Graph(&G, n);
    int u, v, e, s; 
    for(e = 1; e<=m; e++){
    	scanf("%d%d", &u, &v);
    	add_edge(&G, u, v);
	}
	scanf("%d", &s);
	BFS(&G, s);
		
	return 0;
}
