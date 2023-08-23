#include<stdio.h>
#define MAX_Vertices 20
#define MAX_Length 50
#define MAX_Element 50
#define MAX_N 20

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

void make_null_Stack(Stack *S){
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

int min(int x, int y){
	if(x < y)
		return x;
	else 
		return y;
}

int num[MAX_N], min_num[MAX_N];
int  k,cnt;
Stack S;
int on_stack[MAX_N];

void SCC(Graph *pG, int u){
	num[u]= min_num[u] =k;
	k++;
	push_stack(&S, u);
	on_stack[u] =1;
	
	int v;
	for(v=1; v<=pG->n; v++){
		if(adjacent(pG, u, v)){
			if(num[v] < 0){
				SCC(pG, v);
				min_num[u] = min(min_num[u], min_num[v]);
			}
			else if(on_stack[v])
				min_num[u] = min(min_num[u], num[v]);
		}
		
	}
	
	if(num[u] == min_num[u]){
		cnt++;
		int w;
		do{
			w = top(&S);
			pop(&S);
			on_stack[w] = 0;
		}while(w != u);
		
	}
	
}

int main(){
    Graph G;
    freopen("DFS.txt", "r", stdin);
    int n,m,i; // dinh-cung
    scanf("%d%d", &n, &m);
    init_Graph(&G, n);
    int u, v, e; 
    for(e = 1; e<=m; e++){
    	scanf("%d%d", &u, &v);
    	add_edge(&G, u, v);
	}
	
	for(i=1; i<=G.n; i++)
		num[i] = -1;
	k = 1;
	cnt =0;
	make_null_Stack(&S);
	for(u =1; u<=G.n; u++)	
		if(num[u] ==-1)
			SCC(&G, u);
	printf("%d", cnt);
	return 0;
}
