#include<stdio.h>
#define MAX_Vertices 20
#define MAX_Length 50
#define MAX_N 50
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
    int A[MAX_Vertices][MAX_Vertices];
    int n,m;
}Graph;

void init_Graph(Graph *G, int n){
	int i,j;
    G->n = n;
    G->m = 0;
    for(i=1; i<=n; i++)
    	for(j =1; j<=n; j++)
    		G->A[i][j] = 0;
    
}

int quiver =0;

void add_edge(Graph *G, int x, int y){
	G->A[x][y]++;
	if(x == y){
		G->A[x][x] = 1;
		G->A[y][y] = 1;
		quiver++;
	}
		
	if(quiver>=2)
		G->A[x][y]++;
	G->m++;
	
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
int min_cnt;

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
		int cnt= 0;
		int w;
		do{
			w = top(&S);
			pop(&S);
			on_stack[w] = 0;
			cnt++;
		}while(w != u);
		
		if(cnt < min_cnt){
			min_cnt = cnt;
		}
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
	min_cnt = 1000;
	make_null_Stack(&S);
	
	for(u=1; u<=G.n; u++)	
		if(num[u] ==-1)
			SCC(&G, u);	
	printf("%d", min_cnt);
	
	return 0;
}
