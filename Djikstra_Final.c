#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

struct Node {
    uint8_t data;
    struct Node* next;
};

struct Node* createNode(uint8_t data) {
    struct Node* newNode;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
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

 
    for (uint8_t i = 0; i < vertices; i++) {
        distance[i] = UINT8_MAX;
        visited[i] = false;
    }


    distance[start] = 0;


    for (uint8_t count = 0; count < vertices - 1; count++) {
      
        uint8_t minDistance = UINT8_MAX;
        uint8_t minIndex;

        for (uint8_t v = 0; v < vertices; v++) {
            if (!visited[v] && distance[v] <= minDistance) {
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
            }

            currentNode = currentNode->next;
        }
    }
    printf("Shortest path from vertex %d to vertex %d: ", start, end);
    uint8_t currentVertex = end;
    printf("%d ", currentVertex);
    while (currentVertex != start) {
        struct Node* currentNode = graph[currentVertex];
        uint8_t minDistance = UINT8_MAX;
        uint8_t nextVertex;

        while (currentNode != NULL) {
            uint8_t adjacentVertex = currentNode->data;
            uint8_t weight = 1; 

            if (distance[adjacentVertex] < minDistance) {
                minDistance = distance[adjacentVertex];
                nextVertex = adjacentVertex;
            }

            currentNode = currentNode->next;
        }

        currentVertex = nextVertex;
        printf("%d ", currentVertex);
    }
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

    #define START_POINT         (* (volatile uint8_t * ) 0x02000000)
    #define END_POINT           (* (volatile uint8_t * ) 0x02000004)
    #define NODE_POINT          (* (volatile uint8_t * ) 0x02000008)
    #define CPU_DONE            (* (volatile uint8_t * ) 0x0200000c)
    #define NEXT_DIRECTION      (* (volatile uint8_t * ) 0x02000010)    // 0: Straight, 1: Right, 2: left, 3: back 
    #define NODE_REACHED        (* (volatile uint8_t * ) 0x02000014)    // for cpu to write
    START_POINT = 0;
    END_POINT = 7;
    dijkstra(graph, vertices, START_POINT, END_POINT);

    return 0;
}

