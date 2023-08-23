#include <stdio.h>

#define MAX_Length 50
#define MAXN 50

typedef struct{
    int data[MAX_Length];
    int size;
} List;

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
    int n, m;
    int A[MAXN][MAXN];
} Graph;

void init_graph(Graph *pG, int n){
    int i, j;
    pG->n = n;
    for(i=1; i<=pG->n; i++)
        for(j=1; j<=pG->n; j++)
            pG->A[i][j] = 0;
}

void add_edge(Graph *pG, int x, int y){
    pG->A[x][y] = 1;
}

void copy(List *pL1, List *pL2){
	int i;
	makenull(pL2);
	for(i=0; i<pL1->size; i++){
		pL2->data[i] = pL1->data[i];
		pL2->size++;
	}
}

int r[MAXN];

void ranking(Graph *pG){
	int d[MAXN];
	int i, j, u, v;
	for(i=1; i<=pG->n; i++){
		d[i]= 0;
		for(j=1; j<=pG->n; j++)
			if(pG->A[j][i] != 0)
				d[i]++;
	}
	
	List S1;
	makenull(&S1);
	for(j=1; j<=pG->n; j++)
		if(d[j] == 0)
			push_back(&S1, j);
			
	List S2;
	int k = 0;
	while(S1.size > 0){
		makenull(&S2);
		for(i=1; i<=S1.size; i++){
			u = element_at(&S1, i);
			r[u] = k;
			for(v=1; v<=pG->n; v++)
				if(pG->A[u][v] != 0){
					d[v]--;
					while(r[u] < r[v]){
						int temp = r[u];
						r[u] = r[v];
						r[v] = temp;
					}
					if(d[v] == 0)
						push_back(&S2, v);
				}
		}
		k++;
		copy(&S2, &S1);
	} 
}

//void sort(int *x, int *y){
//	int temp = *x;
//	*x = *y;
//	*y = temp;
//}

int main(){
	Graph G;
	int n, m, u , v, i, j;
	freopen("Ranking.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(i=0; i<m; i++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	ranking(&G);
		
	int s=0;
//	for(j=1; j<=G.n; j++){
//		printf("%d\n",r[j]);
//	}
	for(u=1; u<=G.n; u++)
		for(v=1; v<=G.n; v++)
			if(G.A[u][v] != 0)
			{
				while(r[u] < r[v]){
					int temp = r[u];
					r[u] = r[v];
					r[v] = temp;
				}
			
			}
				
	for(j=1; j<=G.n; j++){
		printf("%d\n",r[j]+1);
	}	
	for(i=1; i<=G.n; i++)
		s+=r[i]+1;
	printf("%d", s);
	return 0;
}





