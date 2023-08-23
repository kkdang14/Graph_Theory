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
    int data[MAX_Length];
    int Front, Rear;
} Queue;

void makenullQueue(Queue *Q){
    Q->Front = 0;
    Q->Rear = -1;
}

int emptyQueue(Queue *Q){
    return Q->Front > Q->Rear;
}

void enqueue(Queue *Q, int x){
    Q->Rear++;
    Q->data[Q->Rear] = x;
}

int front(Queue *Q){
    return Q->data[Q->Front];
}

void dequeue(Queue *Q){
    Q->Front++;
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

void topo_sort(Graph *pG, List *pL){
    int i, j, k, v;
    int d[MAXN];
    for(i=1; i<=pG->n; i++){
        d[i] = 0;
        for(j=1; j<=pG->n; j++)
            if(pG->A[j][i] != 0)
                d[i]++;
    }

    Queue Q;
    makenullQueue(&Q);
    for(k = 1; k<=pG->n; k++)
        if(d[k] == 0)
            enqueue(&Q, k);
    makenull(pL);

    while(!emptyQueue(&Q)){
        int u = front(&Q);
        dequeue(&Q);
        push_back(pL, u);
        for(v =1; v<=pG->n; v++)
            if(pG->A[u][v] != 0){
                d[v]--;
                if(d[v] == 0)
                    enqueue(&Q, v);
            }
    }
}

int main(){
    Graph G;
    List L;
    int n, m, u, v, i, j;
    freopen("Topo.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    for(i=0; i<m; i++){
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    topo_sort(&G, &L);

    for(j=1; j<=L.size; j++){
        printf("%d ", element_at(&L, j));
    }
    return 0;
}

