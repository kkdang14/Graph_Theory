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
		if((pG->edges[i].u == x && pG->edges[i].v == y))
			return 1;
	return 0;
}

void add_edge(Graph *pG, int x, int y){
	if(adjacent(pG, x, y) == 1)
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
	makenull(&L);
	for(i=1; i<=pG->n; i++){
		if(adjacent(pG, x, i))
			push_back(&L, i);
	}
	return L;
}

void DFS(Graph *G, int x){
	Stack S;
	makenullStack(&S);
	push_stack(&S, x);
	int mark[MAX_Vertices];
	int i;
	for(i=1; i<=G->n; i++){
		mark[i] = 0;
	}
	while(!empty(&S)){
		int u = top(&S);
		pop(&S);
		if(mark[u] == 1)
			continue;
		printf("%d\n", u);
		mark[u] = 1;
		List L = neighbors(G, u);
		for(i=1; i<=L.size; i++){
			int  v = element_at(&L, i);
			if(mark[v] == 0)
				push_stack(&S, v);
		}
	}
	
}

int main(){
    Graph G;
    freopen("DFS.txt", "r", stdin);
    int n,m,s; // dinh-cung
    scanf("%d%d", &n, &m);
    init_Graph(&G, n);
    int u, v, e; 
    for(e = 1; e<=m; e++){
    	scanf("%d%d", &u, &v);
    	add_edge(&G, u, v);
	}
	
	scanf("%d", &s);
	DFS(&G, s);
		
	return 0;
}
