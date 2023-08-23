#include <stdio.h>
#include <stdlib.h>
#define NO_COLOR 0
#define BLUE 1
#define RED 2
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
	make_null(&L);
	for(i=1; i<=pG->n; i++){
		if(adjacent(pG, x, i))
			push_back(&L, i);
	}
	return L;
}

int color[MAX_N];
int conflict;

void colorize(Graph *pG, int u, int c){
	color[u] = c;
	int v;
	for(v=1; v<=pG->n; v++)
		if(adjacent(pG, u, v)){
			if(color[v] == NO_COLOR)
				colorize(pG, v, 3-c);
			else if(color[v] == color[u])
				conflict = 1;		
		}
}

int main() {
	Graph G;
	freopen("DFS.txt", "r", stdin);
	int n, m, u, v, i,e, j;
	scanf("%d%d", &n, &m);
	init_Graph(&G, n);
	for (e = 0; e < m; e++) {
	    scanf("%d%d", &u, &v);
	    add_edge(&G, u, v);
	}
	
	for(i=1; i<=G.n; i++)
		color[i] = NO_COLOR;
	
	conflict = 0;
	
	for(u=1; u<=G.n; u++)
		if(color[u] == NO_COLOR)
			colorize(&G, u, BLUE);
			
	if(conflict == 1)
		printf("IMPOSSIBLE");
	else{
		for(i=1; i<=G.n; i++)
			if(color[i] == BLUE)
				printf("%d ", color[i]);
		printf("\n");		
		for(j=1; j<=G.n; j++)
			if(color[j] == RED)
				printf("%d ", color[j]);
				
	}	
		
    return 0;
}


