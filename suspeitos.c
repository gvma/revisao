#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct graph GRAPH;
typedef struct node NODE;
typedef struct queue QUEUE;

struct node{
	int data;
	NODE *next;
};

struct queue{
	NODE *front;
	int size;
};

struct graph{
	NODE **adjList;
	bool *visited;
    long long int size;
};

NODE *createNode(int newData){
	NODE *newNode = (NODE*)malloc(sizeof(NODE));
	newNode->data = newData;
	newNode->next = NULL;
	return newNode;
}


NODE *insertEnd(NODE *head, int newData){
	NODE *newNode = createNode(newData);
	if (head == NULL) {
		return newNode;
	} else {
		NODE *current = head;
		while (current->next != NULL){
			current = current->next;
		}
		current->next = newNode;
		return head;
	}
}

QUEUE *createQueue(){
	QUEUE *queue = (QUEUE*)malloc(sizeof(QUEUE));
	queue->front = NULL;
	queue->size = 0;
	return queue;
}

bool isEmpty(QUEUE *queue){
	return queue->size == 0;
}

void enqueue(QUEUE *queue, int newData) {
	queue->front = insertEnd(queue->front, newData);
	queue->size++;
}

NODE *dequeue(QUEUE *queue) {
	if (isEmpty(queue)) {
		return NULL;
	} else {
		NODE *aux = queue->front;
		queue->front = queue->front->next;
		queue->size--;
		return aux;
	}
}

void print_graph(GRAPH *graph) {
    int i, j;
    for (i = 0; i < graph->size; ++i) {
        printf("Vertice %d: ", i);
        NODE *adj_list = graph->adjList[i];
        while (adj_list != NULL) {
            printf("%d -> ", adj_list->data);
            adj_list = adj_list->next;
        }
        printf("\n");
    }
}

GRAPH *createGraph(long long int vertexNumber) {
	GRAPH *graph = (GRAPH*)malloc(sizeof(GRAPH));
	graph->adjList = (NODE**)malloc(sizeof(NODE*) * vertexNumber);
	graph->visited = malloc(sizeof(bool) * vertexNumber);
	int i;
	for (i = 0; i < vertexNumber; i++) {
		graph->adjList[i] = (NODE*)malloc(sizeof(NODE));
		graph->adjList[i] = NULL;
		graph->visited[i] = false;
	}
    graph->size = vertexNumber;
	return graph;
}

void DFS(GRAPH *graph, int source, int *count) {
	if (graph->visited[source] == true) {
        return;
    }
    graph->visited[source] = true;
    NODE *adj_list = graph->adjList[source];
    *count += 1;
    while (adj_list != NULL) {
        // printf("cheguei em %d\n", adj_list->data);
        DFS(graph, adj_list->data, count);
        adj_list = adj_list->next;
    }
}

void BFS(GRAPH *graph, int source, long long int *distances){
	graph->visited[source] = true;
    QUEUE *vertex_queue = createQueue(), *distances_queue = createQueue();
    enqueue(vertex_queue, source);
    enqueue(distances_queue, 0);
    distances[source] = 0;
    while (!isEmpty(vertex_queue)) {
        NODE *vertex_dequeue = dequeue(vertex_queue);
        NODE *distance_dequeue = dequeue(distances_queue);
        NODE *adj_list = graph->adjList[vertex_dequeue->data];
        while (adj_list != NULL) {
            int vertice_destino = adj_list->data;
            int distancia_atual = distance_dequeue->data + 1;
            if (distancia_atual < distances[vertice_destino]) {
                distances[vertice_destino] = distancia_atual;
                enqueue(vertex_queue, vertice_destino);
                enqueue(distances_queue, distancia_atual);
            }
            adj_list = adj_list->next;
        }
    }
}

void addEdge(GRAPH *graph, int v1, int v2)
{
	NODE *vertex = createNode(v2);
	vertex->next = graph->adjList[v1];
	graph->adjList[v1] = vertex;
	NODE *vertex1 = createNode(v1);
	vertex1->next = graph->adjList[v2];
	graph->adjList[v2] = vertex1;
}

int main() {
    while (1) {
        int numero_de_estudantes, numero_de_grupos;
        scanf("%d%d", &numero_de_estudantes, &numero_de_grupos);
        if (!numero_de_estudantes && !numero_de_grupos) {
            break;
        }
        GRAPH *graph = createGraph(numero_de_estudantes);
        int i;
        for (i = 0; i < numero_de_grupos; ++i) {
            int sz, j;
            scanf("%d", &sz);
            int array[sz];
            for (j = 0; j < sz; ++j) {
                scanf("%d", &array[j]);
            }
            for (j = 1; j < sz; ++j) {
                addEdge(graph, array[j - 1], array[j]);
            }
            // print_graph(graph);
        }
        int count = 0;
        DFS(graph, 0, &count);
        printf("%d\n", count);
        for (i = 0; i < numero_de_estudantes; ++i) {
            graph->visited[i] = false;
        }
    }
    return 0;
}