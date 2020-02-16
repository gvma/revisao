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
    for (i = 1; i < graph->size; ++i) {
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

void DFS(GRAPH *graph, int source, int *distances, int actualDistance) {
	NODE *current = graph->adjList[source];
	while (current != NULL) {
		if (actualDistance + 1 <= distances[current->data]){
			distances[current->data] = actualDistance + 1;
			DFS(graph, current->data, distances, actualDistance + 1);
		}
		current = current->next;
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
    long long int numero_de_vertices, numero_de_arestas, casos_de_teste;
    int i, j;
    GRAPH *graph;
    scanf("%lld", &casos_de_teste);
    for (i = 0; i < casos_de_teste; ++i) {
        scanf("%lld%lld" ,&numero_de_vertices, &numero_de_arestas);
        graph = createGraph(numero_de_vertices + 1);
        for (j = 0; j < numero_de_arestas; ++j) {
            int u, v;
            scanf("%d%d", &u, &v);
            addEdge(graph, u, v);
        }
        long long int distances[numero_de_vertices + 1];
        for (j = 0; j < graph->size; ++j) {
            distances[j] = 10000;
        }
        BFS(graph, 1, distances);
        if (distances[numero_de_vertices] == 10000) {
            printf("-1\n");
        } else {
            printf("%lld\n", distances[numero_de_vertices]);
        }
    }
    return 0;
}