#include<stdio.h>
#define MAX_Vertices 20
#define MAX_Length 50
#define MAX_Element 50

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
	make_null(&L);
	for(i=1; i<=G->n; i++){
		if(G->A[i][x] == 1)
			push_back(&L, i);
	}
	return L;
}

List DFS(Graph *G, int x, int parent[]){
	Stack S;
	makenullStack(&S);
	push_stack(&S, x);
	parent[x] = 0;
	List list_dfs;
	make_null(&list_dfs);
	int mark[MAX_Vertices];
	int i,j;
	for(i=1; i<=G->n; i++){
		mark[i] = 0;
	}
	while(!empty(&S)){
		int u = top(&S);
		pop(&S);
		if(mark[u] == 1)
			continue;
//		printf("Duyet: %d\n", u);
		push_back(&list_dfs, u);
		mark[u] = 1;
		List L = neighbors(G, u);
		for(i=1; i<=L.size; i++){
			int  v = element_at(&L, i);
			if(mark[v] == 0){
				push_stack(&S, v);
				parent[v] = u; 
			}
		}
	}
	
	return list_dfs;
	
}

int main(){
    Graph G;
    freopen("DFS2.txt", "r", stdin);
    int n,m,i,j; // dinh-cung
    scanf("%d%d", &n, &m);
    init_Graph(&G, n);
    int u, v, e; 
    for(e = 1; e<=m; e++){
    	scanf("%d%d", &u, &v);
    	add_edge(&G, u, v);
	}
	int parent[MAX_Vertices];
	for(i=1; i<=G.n; i++)
		parent[i] = -1;
	
	int mark_dfs[MAX_Vertices];
	for(i=1; i<=G.n; i++){
		mark_dfs[i] = 0;
	}
	for(i=1; i<=G.n; i++){
		if(mark_dfs[i] == 0){
			List dfs = DFS(&G, i, parent);
			for(j=1; j<=dfs.size; j++){
				int k = element_at(&dfs, j);
//				printf("Duyet: %d\n", k);
				mark_dfs[k] = 1;
			}		
		}
	}
	for(u=1; u<=G.n; u++)
		printf("%d %d\n", u, parent[u]);	
	return 0;
}
