#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

struct Node {
    uint8_t data;
    struct Node* next;
};

struct Node nodes[34];
int currentNodeIndex = 0;

struct Node* createNode(uint8_t data) {
    if (currentNodeIndex > 34) {
        fprintf(stderr, "Exceeded maximum number of nodes.\n");
        exit(EXIT_FAILURE);
    }
    nodes[currentNodeIndex].data = data;
    nodes[currentNodeIndex].next = NULL;
    return &nodes[currentNodeIndex++];
}

void addEdge(struct Node** graph, uint8_t src, uint8_t dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph[src];
    graph[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph[dest];
    graph[dest] = newNode;
}
void dijkstra(struct Node** graph, uint8_t vertices, uint8_t start, uint8_t end) {
    uint8_t distance[vertices];
    bool visited[vertices];
    uint8_t predecessor[vertices];

    for (uint8_t i = 0; i < vertices; i++) {
        distance[i] = UINT8_MAX;
        visited[i] = false;
        predecessor[i] = UINT8_MAX;
    }

    distance[start] = 0;

    for (uint8_t count = 0; count < vertices - 1; count++) {
        uint8_t minDistance = UINT8_MAX;
        uint8_t minIndex;

        for (uint8_t v = 0; v < vertices; v++) {
            if (!visited[v] && distance[v] < minDistance) {
                minDistance = distance[v];
                minIndex = v;
            }
        }

        visited[minIndex] = true;

        struct Node* currentNode = graph[minIndex];
        while (currentNode != NULL) {
            uint8_t adjacentVertex = currentNode->data;
            uint8_t weight = 1; 

            if (!visited[adjacentVertex] && distance[minIndex] != UINT8_MAX && distance[minIndex] + weight < distance[adjacentVertex]) {
                distance[adjacentVertex] = distance[minIndex] + weight;
                predecessor[adjacentVertex] = minIndex;
            }

            currentNode = currentNode->next;
        }
    }

    printf("Shortest path from vertex %d to vertex %d: ", start, end);
    uint8_t currentVertex = end;
    while (currentVertex != start) {
        printf("%d ", currentVertex);
        currentVertex = predecessor[currentVertex];
        if (currentVertex == UINT8_MAX) {
            printf("\nNo path from %d to %d.\n", start, end);
            return;
        }
    }
    printf("%d\n", start);
}
  
int main() {
    uint8_t vertices = 30;
  
    struct Node* graph[vertices];


    for (int i = 0; i < vertices; i++) {
        graph[i] = NULL;
    }


    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 29);
    addEdge(graph, 2, 3);
    addEdge(graph, 2, 8);
    addEdge(graph, 3, 4);
    addEdge(graph, 3, 28);
    addEdge(graph, 4, 5);
    addEdge(graph, 4, 6);
    addEdge(graph, 6, 7);
    addEdge(graph, 7, 8);
    addEdge(graph, 8, 9);
    addEdge(graph, 8, 12);
    addEdge(graph, 9, 10);
    addEdge(graph, 9, 11);
    addEdge(graph, 12, 13);
    addEdge(graph, 12, 19);
    addEdge(graph, 13, 14);
    addEdge(graph, 14, 15);
    addEdge(graph, 14, 16);
    addEdge(graph, 16, 17);
    addEdge(graph, 16, 18);
    addEdge(graph, 18, 19);
    addEdge(graph, 19, 20);
    addEdge(graph, 20, 21);
    addEdge(graph, 20, 24);
    addEdge(graph, 20, 29);
    addEdge(graph, 21, 22);
    addEdge(graph, 21, 23);
    addEdge(graph, 24, 25);
    addEdge(graph, 25, 26);
    addEdge(graph, 26, 27);
    addEdge(graph, 26, 28);
    addEdge(graph, 28, 29);

int START_POINT = 0;
int END_POINT = 7;  // for cpu to write
    START_POINT = 0;
    END_POINT = 7;
    dijkstra(graph, vertices, START_POINT, END_POINT);
    
    return 0;
}

