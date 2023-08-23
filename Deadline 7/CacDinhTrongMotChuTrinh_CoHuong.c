#include <stdio.h>
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define MAX_N 100
#define MAX_Length 50
#define MAX_Element 50
#define MAX_Vertices 20

typedef struct{
	int data[MAX_Length];
	int size;
}List;

void make_null(List *L){
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
	int data[MAX_Element];
	int size;
}Stack;

void makenullStack(Stack *S){
	S->size = 0;
}

int empty(Stack *S){
	return S->size == 0;
}

void push_stack(Stack *S, int x){
	S->data[S->size] = x;
	S->size++; 
}

int top(Stack *S){
	return S->data[S->size-1];
}

void pop(Stack *S){
	S->size--;
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
		if((pG->edges[i].u == x && pG->edges[i].v == y) )
			return 1;
	return 0;
}

void add_edge(Graph *pG, int x, int y){
	if(adjacent(pG, x, y)==1)
		return;
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
	make_null(&L);
	for(i=1; i<=pG->n; i++){
		if(adjacent(pG, x, i))
			push_back(&L, i);
	}
	return L;
}
int color[MAX_N], has_circle;
List L;
void DFSr(Graph *pG, int u) {
	int v;
	make_null(&L);
	printf("%d ", u);	
	color[u] = GRAY; 		
	for (v = 1; v <= pG->n; v++)
		if (adjacent(pG, u, v)){
			if(color[v] == WHITE){
				DFSr(pG, v);
			}
			else if(color[v] == GRAY){
				has_circle = 1;
				push_back(&L, v);
			}		    		
		}	
	color[u] = BLACK;
}

//int connected(Graph *pG) {
//	for (int u = 1; u <= pG->n; u++)
//		mark[u] = 0;
//	DFS(pG, 1);
//	for (int u = 1; u <= pG->n; u++)
//		if (mark[u] == 0)
//			return 0; 	
//	return 1;		
//}


int main() {
	Graph G;
	freopen("DFS.txt", "r", stdin);
	int n, m, u, v, e;
	scanf("%d%d", &n, &m);
	init_Graph(&G, n);
	for (e = 0; e < m; e++) {
	    scanf("%d%d", &u, &v);
	    add_edge(&G, u, v);
	}

	for (u = 1; u <= G.n; u++) {
		color[u] = WHITE;
	}
	has_circle =0;
	for (u = 1; u <= G.n; u++)
		if(color[u] == WHITE){
			DFSr(&G, u);	 	
		}
	
	if(has_circle == 1)
		for(e=1; e<=L.size; e++){
			int k = element_at(&L, e);
			printf("%d ", k);
		}
	else
		printf("-1");
		
    return 0;
}


