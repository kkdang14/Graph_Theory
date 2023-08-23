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
	int u,v;
}Edge;

typedef struct{
	int n,m;
	Edge edges[MAX_Vertices];
}Graph;

void init_Graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
}

int adjacent(Graph *pG, int x, int y){
	int i;
	for(i=0; i< pG->m; i++)
		if((pG->edges[i].u == x && pG->edges[i].v == y) || (pG->edges[i].u == y && pG->edges[i].v == x))
			return 1;
	return 0;
}

void add_edge(Graph *pG, int x, int y){
	pG->edges[pG->m].u = x;
	pG->edges[pG->m].v = y;
	pG->m++;
}

int degree(Graph *pG, int x){
	int i, deg = 0;
	for(i=0; i< pG->m; i++){
		if(pG->edges[i].u == x)
			deg++;
		if(pG->edges[i].v == x)
			deg++;
	}
	return deg;
}

List neighbors(Graph *pG, int x){
	int i;
	List L;
	makenull(&L);
	for(i=1; i<=pG->n; i++){
		if(adjacent(pG, x, i))
			push_back(&L, i);
	}
	return L;
}

int mark[MAX_Vertices];
int parent[MAX_Vertices];

List BFS(Graph *G, int x, int mark[], int parent[]){
	Queue Q;
	makenullQueue(&Q);
	push_queue(&Q, x);
	parent[x] =-1;
	List list_bfs;
	makenull(&list_bfs);
	int j;
	while(!emptyQueue(&Q)){
		int u = top(&Q);
		pop(&Q);
		if(mark[u] == 1)
			continue;
//		printf("Duyet: %d\n", u);
		push_back(&list_bfs, u);
		mark[u] = 1;
		List L = neighbors(G, u);
		for(j=1; j<=L.size; j++){
			int v = element_at(&L, j);
			if(mark[v] == 0){
				push_queue(&Q, v);
				if(parent[v] ==0)
					parent[v]= u;
			}
				
		}
	}
	
	return list_bfs;
}
int main(){
    Graph G;
    freopen("BFS.txt", "r", stdin);
    int n,m; // dinh-cung
    scanf("%d%d", &n, &m);
    init_Graph(&G, n);
    int u, v, e,i; 
    for(e = 1; e<=m; e++){
    	scanf("%d%d", &u, &v);
    	add_edge(&G, u, v);
	}
	for(u=1; u<=G.n; u++){
		mark[u]= 0;
		parent[u]=0;
	}
	for(i=1; i<=G.n; i++){
		if(mark[i] == 0){
			List bfs = BFS(&G, i, mark, parent);
			for(v=1; v<=bfs.size; v++){
				int k = element_at(&bfs, v);
				mark[k] = 1;
			}	
		}
	}	
	
	for(e=1; e<=G.n; e++)
		printf("%d %d\n",e, parent[e]);
	return 0;
}
