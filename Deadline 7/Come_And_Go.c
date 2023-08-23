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

void add_edge(Graph *G, int x, int y, int p){
	G->A[x][y] =1;
	if(p>1)
		G->A[y][x]=1;
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
    int u, v, e, t; 
    for(e = 1; e<=m; e++){
    	scanf("%d%d%d", &u, &v, &t);
    	add_edge(&G, u, v, t);
	}
	
	for(i=1; i<=G.n; i++)
		num[i] = -1;
	k = 1;
	cnt =0;
	make_null_Stack(&S);
	for(u =1; u<=G.n; u++)	
		if(num[u] ==-1)
			SCC(&G, u);
			
	if(cnt == 1)
		printf("OKIE");
	else 
		printf("NO");
	return 0;
}
