// Cho một đồ thị vô hướng đơn. Hãy in ra thứ tự của các đỉnh khi duyệt đồ thị theo chiều rộng bắt đầu từ đỉnh 1.

// Nếu đồ thị không liên thông, sau khi duyệt xong lần 1, tìm đỉnh có chỉ số nhỏ nhất chưa duyệt mà duyệt nó, và cứ tiếp tục như thế cho đến khi tất cả các đỉnh đều được duyệt.

// Quy ước:

// Các đỉnh kề của 1 đỉnh được liệt kê theo thứ tự tăng dần
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

typedef int ElementType;

typedef struct Node {
    ElementType Data;
    struct Node *Next;
} Node;

typedef struct {
    Node *Front, *Rear;
} Queue;

void make_null_queue (Queue *pQ){
    Node *Header = (Node*)malloc(sizeof(Node));
    Header->Next = NULL;
    pQ->Front = Header;
    pQ->Rear = Header;
}

void enqueue (Queue *pQ, int x){
    pQ->Rear->Next =  (Node*)malloc (sizeof (Node));
    pQ->Rear = pQ->Rear->Next;
    pQ->Rear->Data = x;
    pQ->Rear->Next = NULL;
}

ElementType dequeue (Queue *pQ){
    Node *Temp;
    Temp = pQ->Front;
    pQ->Front = pQ->Front->Next;
    free(Temp);
    return pQ->Front->Data;
}

typedef struct{
	int n, m;
	int A[MAX_N][MAX_N];
} Graph;

void init_graph (Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; i <= n; i++)
			pG->A[i][j] = 0;
}

void add_edge (Graph *pG, int u, int v) {
	pG->A[u][v] = 1;
    pG->A[v][u] = 1; // Undirected Graph
	pG->m++;
}

void read_graph (Graph *pG){
    int n, m;
    scanf ("%d %d", &n, &m);
    init_graph (pG, n);
    for (int i = 0; i < m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(pG, u, v);
    }
}

int mark[MAX_N];

void bfs(Graph *pG, int s){
    Queue Q;
    make_null_queue(&Q);
    enqueue(&Q, s);
    while (Q.Front != Q.Rear){
        int u = dequeue(&Q);
        if (!mark[u]){
            mark[u] = 1;
            printf("%d\n", u);
            for (int v = 1; v <= pG->n; v++)
                if (pG->A[u][v])
                    enqueue(&Q, v);
        }
    }
}

int main (){
    Graph G;    
    read_graph (&G);
    for(int i = 1; i <= G.n; i++)
        mark[i] = 0;
    for(int i = 1; i <= G.n; i++)
        bfs(&G, i);
}