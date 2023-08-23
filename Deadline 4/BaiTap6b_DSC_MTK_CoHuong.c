#include<stdio.h>
#define MAX_Vertices 500

typedef struct{
	int u,v;
}Edge;

typedef struct{
	int n,m;
	Edge edges[MAX_Vertices];
}Graph;

void init_graph(Graph *pG, int n){
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

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void sort(int array[], int size) {
  	int step,i;
	for(step = 0; step < size - 1; step++) {
		int min_idx = step;
    	for(i = step + 1; i < size; i++) {
      		if (array[i] < array[min_idx])
        	min_idx = i;
    }
    swap(&array[min_idx], &array[step]);
  }
}

void neighbors(Graph *pG, int u){
	int e,i;
	int ads[MAX_Vertices];
	int k;
	for(e=0; e<pG->m; e++){
		if(pG->edges[e].u == u){
			ads[k] = pG->edges[e].v;
			k++;	
		}
		sort(ads, k);
	}
	
	for(i=0; i<k; i++)
		printf("%d ", ads[i]);
	printf("\n");
}


int main(){
    Graph G;
    freopen("neighbor_2.txt", "r", stdin);
    int n,m; // dinh-cung
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    int u, v, e; 
    for(e = 1; e<=m; e++){
    	scanf("%d%d", &u, &v);
    	add_edge(&G, u, v);
	}
	int i,j;
	for(i=1; i<=G.n; i++){
		printf("neighbour(%d) = ", i);
		neighbors(&G, i);
	}
	return 0;
}
