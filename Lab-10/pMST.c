#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_EDGES 1000
#define MAX_VERTICES 100

// Define a structure for a graph edge
typedef struct Edge
{
    int src;
    int dest;
    int weight;
} Edge;

// Define a structure for a graph
typedef struct Graph
{
    int numVertices;
    int numEdges;
    Edge *edges;
} Graph;

// Create a new graph with the specified number of vertices and edges
Graph *createGraph(int numVertices, int numEdges)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->numEdges = numEdges;
    graph->edges = (Edge *)malloc(MAX_EDGES * sizeof(Edge));
    return graph;
}

// Add an edge to the graph
void addEdge(Graph *graph, int src, int dest, int weight)
{
    graph->edges[graph->numEdges].src = src;
    graph->edges[graph->numEdges].dest = dest;
    graph->edges[graph->numEdges].weight = weight;
    graph->numEdges++;
}

// Define a structure for a node in the r-way heap
typedef struct Node
{
    int vertex;
    int key;
} Node;

// Define a structure for the r-way heap
typedef struct PriorityQueue
{
    int r;
    int size;
    int capacity;
    Node *heap;
} PriorityQueue;

// Create a new r-way heap with the specified number of children per node and maximum capacity
PriorityQueue *createPriorityQueue(int r, int capacity)
{
    PriorityQueue *queue = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    queue->r = r;
    queue->size = 0;
    queue->capacity = capacity;
    queue->heap = (Node *)malloc(capacity * sizeof(Node));
    return queue;
}

// Swap the nodes at the specified indices in the r-way heap
void swap(PriorityQueue *queue, int index1, int index2)
{
    Node temp = queue->heap[index1];
    queue->heap[index1] = queue->heap[index2];
    queue->heap[index2] = temp;
}

// Percolate up the node at the specified index in the r-way heap
void heapifyUp(PriorityQueue *queue, int index)
{
    int parent = (index - 1) / queue->r;
    while (index > 0 && queue->heap[index].key < queue->heap[parent].key)
    {
        swap(queue, index, parent);
        index = parent;
        parent = (index - 1) / queue->r;
    }
}

// Percolate down the node at the specified index in the r-way heap
void heapifyDown(PriorityQueue *queue, int index)
{
    int child = queue->r * index + 1;
    while (child < queue->size)
    {
        int minChild = child;
        int i;
        for (i = 1; i < queue->r && i + child < queue->size; i++)
        {
            if (queue->heap[i + child].key < queue->heap[minChild].key)
            {
                minChild = i + child;
            }
        }
        if (queue->heap[index].key > queue->heap[minChild].key)
        {
            swap(queue, index, minChild);
            index = minChild;
            child = queue->r * index + 1;
        }
        else
        {
            break;
        }
    }
}

// Insert a new element with the specified priority into the r-way heap
void insert(PriorityQueue *queue, int vertex, int key)
{
    if (queue->size == queue->capacity)
    {
        printf("Priority queue is full, cannot insert\n");
        return;
    }
    queue->heap[queue->size].vertex = vertex;
    queue->heap[queue->size].key = key;
    queue->size++;
    heapifyUp(queue, queue->size - 1);
}

// Remove and return the element with the minimum priority from the r-way heap
Node extractMin(PriorityQueue *queue)
{
    if (queue->size == 0)
    {
        printf("Priority queue is empty, cannot extract minimum\n");
        Node emptyNode;
        emptyNode.vertex = -1;
        emptyNode.key = INT_MAX;
        return emptyNode;
    }
    Node minNode = queue->heap[0];
    queue->size--;
    queue->heap[0] = queue->heap[queue->size];
    heapifyDown(queue, 0);
    return minNode;
}

// Prim's Algorithm for Minimum Spanning Tree using r-way heaps
void primMST(Graph *graph, int startVertex)
{
    // Create an array to track the parent of each vertex in the MST
    int parent[graph->numVertices];
    // Create an array to track the key of each vertex in the r-way heap
    int key[graph->numVertices];
    // Create a boolean array to track which vertices have been added to the MST
    int inMST[graph->numVertices];
    // Initialize all keys to infinity, all parents to -1, and all vertices to not in MST
    int i;
    for (i = 0; i < graph->numVertices; i++)
    {
        key[i] = INT_MAX;
        parent[i] = -1;
        inMST[i] = 0;
    }
    // Set the key of the starting vertex to 0 and add it to the r-way heap
    key[startVertex] = 0;
    int r = 2 + (graph->numEdges / graph->numVertices);
    PriorityQueue *queue = createPriorityQueue(r, graph->numVertices);
    insert(queue, startVertex, 0);
    // Loop until the r-way heap is empty
   while (queue->size > 0)
    {
        // Extract the vertex with the minimum key from the r-way heap
        Node minNode = extractMin(queue);
        int u = minNode.vertex;
        // Add the vertex to the MST and set its inMST value to true
        inMST[u] = 1;
        // For each neighbor of the vertex that is not already in the MST, update its key if necessary and add it to the r-way heap
        int j;
        for (j = 0; j < graph->numEdges; j++)
        {
            Edge edge = graph->edges[j];
            if (edge.src == u && !inMST[edge.dest] && edge.weight < key[edge.dest])
            {
                key[edge.dest] = edge.weight;
                parent[edge.dest] = u;
                insert(queue, edge.dest, key[edge.dest]);
            }
            else if (edge.dest == u && !inMST[edge.src] && edge.weight < key[edge.src])
            {
                key[edge.src] = edge.weight;
                parent[edge.src] = u;
                insert(queue, edge.src, key[edge.src]);
            }
        }
    }
    // Print the MST
    printf("Minimum Spanning Tree:\n");
    int totalWeight = 0;
    for (i = 0; i < graph->numVertices; i++)
    {
        if (parent[i] != -1)
        {
            printf("(%d, %d) - %d\n", parent[i], i, key[i]);
            totalWeight += key[i];
        }
    }
    printf("Total weight of MST: %d\n", totalWeight);
}
void freeGraph(Graph *graph)
{
    free(graph->edges);
    free(graph);
}
int main()
{
    // Create a graph with 6 vertices and 10 edges
    int V, E;
    printf("\nEnter the no. of vertices and edges:\n");
    scanf("%d %d", &V, &E);
    Graph *graph = createGraph(V, E);
    for (int i = 0; i < E; i++)
    {
        int u, v, wt;
        printf("\nEnter the vertices and the weight of their edge:");
        scanf("%d %d %d", &u, &v, &wt);
        addEdge(graph, u, v, wt);
    }

    primMST(graph, 0);

    // Free the memory allocated for the graph
    freeGraph(graph);

    return 0;
}