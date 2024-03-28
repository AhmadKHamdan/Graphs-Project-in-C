// AHMAD HAMDAN 1210241 SEC 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_CITIES 25

struct node
{
    char city[20];
    int distance;
    struct node *next;
    struct node *previous;
};

struct Queue
{
    int front;
    int rear;
    int size;
    int capacity;
    int *array;
};

// Function prototypes
struct node *createNode(char city[20], int distance);
void addEdge(struct node **adjacencyList, int *count, char *city1, char *city2, int distance);
void breadthFirstSearch(struct node **adjacencyList, int count, char *sourceCity, char *destinationCity, int mode);
void enqueue(struct Queue *queue, int item);
int dequeue(struct Queue *queue);
bool isQueueEmpty(struct Queue *queue);
void createQueue(struct Queue *queue, int capacity);
int getCityIndex(struct node **adjacencyList, int count, char *city);
void printShortestPath(struct node **adjacencyList, int count, int *previous, int destinationIndex, int mode);
void dijkstra(struct node **adjacencyList, int count, char *sourceCity, char *destinationCity, int mode);
 
int main()
{
    int count = 0; // Keep count of the number of cities

    // Creating my map and setting all of the indices as NULL
    struct node **map = (struct node **)malloc(MAX_CITIES * sizeof(struct node *));
    for (int i = 0; i < MAX_CITIES; i++)
    {
        map[i] = NULL;
    }

    // Creating the main menu of the program
    int input = 0;
    char srcCity[20] = "", destCity[20];
    while (input != 5)
    {
        printf("\n1- Load the cities from the file\n");
        printf("2- Enter the source city\n");
        printf("3- Enter the destination city\n");
        printf("4- Save last result\n");
        printf("5- Save and Exit\n");
        printf(".......................\n");
        printf("Please choose an operation: ");
        scanf("%d", &input);
        printf("\n");

        if (input == 1)
        {
            int distance;
            char srcCity[20], desCity[20];
            FILE *file = fopen("Cities.txt", "r");
            while (fscanf(file, "%s %s %dkm", srcCity, desCity, &distance) != EOF)
            {
                addEdge(map, &count, srcCity, desCity, distance);
            }
            printf("Cities have been loaded\n");
        }
        if (input == 2)
        {
            printf("Enter the source city: ");
            scanf("%s", srcCity);
        }
        if (input == 3)
        {
            if (strcmp(srcCity, "") == 0)
            {
                printf("Invalid! You need to enter a source city\n");
            }
            else
            {
                printf("Enter the destination city: ");
                scanf("%s", destCity);
                printf("\nBFS output:\n");
                breadthFirstSearch(map, count, srcCity, destCity, 0);
                printf("\nDijkstra output:\n");
                dijkstra(map, count, srcCity, destCity, 0);
            }
        }
        if (input == 4)
        {
            breadthFirstSearch(map, count, srcCity, destCity, 1);
            dijkstra(map, count, srcCity, destCity, 1);
            printf("Latest result has been saved to the file\n");
        }
        if (input == 5)
        {
            breadthFirstSearch(map, count, srcCity, destCity, 1);
            dijkstra(map, count, srcCity, destCity, 1);
            printf("Goodbye! <3\n");
            // Cleanup code (free allocated memory)
            for (int i = 0; i < MAX_CITIES; i++)
            {
                struct node *currentNode = map[i];
                while (currentNode != NULL)
                {
                    struct node *temp = currentNode;
                    currentNode = currentNode->next;
                    free(temp);
                }
            }
            free(map);
        }
    }

    return 0;
}

// Function to create a node in the graph
struct node *createNode(char city[20], int distance)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    strncpy(newNode->city, city, sizeof(newNode->city));
    newNode->distance = distance;
    newNode->next = NULL;
    newNode->previous = NULL;
    return newNode;
}

// Function to add an edge between two nodes (cities)
void addEdge(struct node **adjacencyList, int *count, char *city1, char *city2, int distance)
{
    struct node *newNode = createNode(city2, distance);

    int i;

    for (i = 0; i < MAX_CITIES; i++)
    {
        if (adjacencyList[i]->city != NULL && strcmp(adjacencyList[i]->city, city1) == 0)
        {
            break;
        }
    }

    if (i == MAX_CITIES)
    {
        struct node *headNode = createNode(city1, 0);
        adjacencyList[*count] = headNode;
        headNode->next = newNode;
        newNode->previous = headNode;
        (*count)++;
    }
    else
    {
        struct node *currentNode = adjacencyList[i];
        while (currentNode->next != NULL)
            currentNode = currentNode->next;
        currentNode->next = newNode;
        newNode->previous = currentNode;
    }
}

// Function to enqueue an item into the queue
void enqueue(struct Queue *queue, int item)
{
    if (queue->rear == queue->capacity - 1)
    {
        printf("Queue is full.\n");
        return;
    }
    queue->rear++;
    queue->array[queue->rear] = item;
    queue->size++;
}

// Function to dequeue an item from the queue
int dequeue(struct Queue *queue)
{
    if (isQueueEmpty(queue))
    {
        printf("Queue is empty.\n");
        return -1;
    }
    int item = queue->array[queue->front];
    queue->front++;
    queue->size--;
    return item;
}

// Function to check if the queue is empty
bool isQueueEmpty(struct Queue *queue)
{
    return queue->size == 0;
}

// Function to initialize the queue
void createQueue(struct Queue *queue, int capacity)
{
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    queue->array = (int *)malloc(capacity * sizeof(int));
}

// Function to get the index of a chosen city
int getCityIndex(struct node **adjacencyList, int count, char *city1)
{
    for (int i = 0; i < count; i++)
    {
        if (adjacencyList[i] != NULL && strcmp(adjacencyList[i]->city, city1) == 0)
        {
            return i;
        }
    }
    return -1;
}

// Function to print the shortest path
void printShortestPath(struct node **adjacencyList, int count, int *previous, int destinationIndex, int mode)
{
    int path[MAX_CITIES];
    int pathIndex = 0;
    FILE *fp = fopen("shortest_distance.txt", "a");

    int currentIndex = destinationIndex;
    while (currentIndex != -1)
    {
        path[pathIndex++] = currentIndex;
        currentIndex = previous[currentIndex];
    }
    for (int i = pathIndex - 1; i >= 0; i--)
    {
        int currentIndex = path[i];
        if (mode)
            fprintf(fp, "%s", adjacencyList[currentIndex]->city);
        else
            printf("%s", adjacencyList[currentIndex]->city);
        if (i > 0)
        {
            int nextIndex = path[i - 1];
            struct node *currentNode = adjacencyList[currentIndex];
            struct node *nextNode = adjacencyList[nextIndex];
            struct node *tempNode = currentNode->next;
            while (tempNode != NULL)
            {
                if (strcmp(tempNode->city, nextNode->city) == 0)
                {
                    if (mode)
                        fprintf(fp, " -> (%d km) ", tempNode->distance);
                    else
                        printf(" -> (%d km) ", tempNode->distance);
                    break;
                }
                tempNode = tempNode->next;
            }
        }
    }
    fclose(fp);
    if (mode)
        printf("\n");
}

// Function to perform breadth-first search
void breadthFirstSearch(struct node **adjacencyList, int count, char *sourceCity, char *destinationCity, int mode)
{
    int visited[MAX_CITIES];
    int distance[MAX_CITIES];
    int previous[MAX_CITIES]; 
    for (int i = 0; i < MAX_CITIES; i++)
    {
        visited[i] = 0;
        distance[i] = 9999; // Initialize all distances to infinity
        previous[i] = -1;   // Initialize previous cities to -1
    }

    int sourceIndex = -1;
    int destinationIndex = -1;
    for (int i = 0; i < count; i++)
    {
        if (adjacencyList[i] != NULL)
        {
            if (strcmp(adjacencyList[i]->city, sourceCity) == 0)
            {
                sourceIndex = i;
                distance[i] = 0; // Distance to the source city is 0
            }
            if (strcmp(adjacencyList[i]->city, destinationCity) == 0)
            {
                destinationIndex = i;
            }
        }
    }

    if (sourceIndex == -1 || destinationIndex == -1)
    {
        printf("Source or destination city not found.\n");
        return;
    }

    struct Queue queue;
    createQueue(&queue, count);
    visited[sourceIndex] = 1;
    enqueue(&queue, sourceIndex);

    while (!isQueueEmpty(&queue))
    {
        int currentIndex = dequeue(&queue);

        if (currentIndex == destinationIndex)
        {
            // Destination city reached, terminate the search
            break;
        }

        struct node *currentNode = adjacencyList[currentIndex]->next;
        while (currentNode != NULL)
        {
            int neighborIndex = getCityIndex(adjacencyList, count, currentNode->city);
            if (neighborIndex != -1 && visited[neighborIndex] == 0)
            {
                visited[neighborIndex] = 1;
                enqueue(&queue, neighborIndex);
                distance[neighborIndex] = distance[currentIndex] + currentNode->distance;
                previous[neighborIndex] = currentIndex; // Set the previous city for backtracking the shortest path
            }

            currentNode = currentNode->next;
        }
    }

    if (distance[destinationIndex] != 9999)
    {
        // Print the shortest path
        FILE *fp = fopen("shortest_distance.txt", "a");

        if (mode)
        {
            printShortestPath(adjacencyList, count, previous, destinationIndex, mode);

            // Print the total distance
            fprintf(fp, "\nTotal distance: %d km\n", distance[destinationIndex]);

            fprintf(fp, "BFS result:\n*********\n");
        }
        else
        {
            printf("From %s to %s:\n", adjacencyList[sourceIndex]->city, adjacencyList[destinationIndex]->city);

            printf("Shortest path: ", adjacencyList[sourceIndex]->city, adjacencyList[destinationIndex]->city);
            printShortestPath(adjacencyList, count, previous, destinationIndex, mode);

            // Print the total distance
            printf("\nTotal distance: %d km\n", distance[destinationIndex]);
        }
        fclose(fp);
    }
    else
    {
        printf("No path found from %s to %s.\n", adjacencyList[sourceIndex]->city, adjacencyList[destinationIndex]->city);
    }
}

// Function to implement dijkstra
void dijkstra(struct node **adjacencyList, int count, char *sourceCity, char *destinationCity, int mode)
{
    int sourceIndex = -1;
    int destinationIndex = -1;

    // Find the indices of the source and destination cities
    for (int i = 0; i < count; i++)
    {
        if (adjacencyList[i] != NULL)
        {
            if (strcmp(adjacencyList[i]->city, sourceCity) == 0)
                sourceIndex = i;
            if (strcmp(adjacencyList[i]->city, destinationCity) == 0)
                destinationIndex = i;
        }
    }

    if (sourceIndex == -1 || destinationIndex == -1)
    {
        printf("Source or destination city not found.\n");
        return;
    }

    // Initialize distance array and visited array
    int *distance = (int *)malloc(count * sizeof(int));
    int *visited = (int *)malloc(count * sizeof(int));
    int *previous = (int *)malloc(count * sizeof(int));
    for (int i = 0; i < count; i++)
    {
        distance[i] = 9999;
        visited[i] = 0;
        previous[i] = -1;
    }

    // Set the distance of the source city to 0
    distance[sourceIndex] = 0;

    // Perform Dijkstra's algorithm
    for (int i = 0; i < count - 1; i++)
    {
        // Find the vertex with the minimum distance value
        int minDistance = 9999;
        int minIndex = -1;
        for (int j = 0; j < count; j++)
        {
            if (visited[j] == 0 && distance[j] <= minDistance)
            {
                minDistance = distance[j];
                minIndex = j;
            }
        }

        // Mark the selected vertex as visited
        visited[minIndex] = 1;

        // Update the distances of the adjacent vertices
        struct node *currentNode = adjacencyList[minIndex]->next;
        while (currentNode != NULL)
        {
            int neighborIndex = getCityIndex(adjacencyList, count, currentNode->city);
            if (neighborIndex != -1 && visited[neighborIndex] == 0 && distance[minIndex] != 9999 &&
                distance[minIndex] + currentNode->distance < distance[neighborIndex])
            {
                distance[neighborIndex] = distance[minIndex] + currentNode->distance;
                previous[neighborIndex] = minIndex;
            }
            currentNode = currentNode->next;
        }
    }
    // Print the shortest path
    FILE *fp = fopen("shortest_distance.txt", "a");

    if (mode)
    {

        printShortestPath(adjacencyList, count, previous, destinationIndex, mode);

        // Print the total distance
        fprintf(fp, "\nTotal distance: %d km\n", distance[destinationIndex]);

        fprintf(fp, "Dijkstra result:\n*********\n");
    }
    else
    {
        printf("From %s to %s:\n", adjacencyList[sourceIndex]->city, adjacencyList[destinationIndex]->city);

        printf("Shortest path: ", adjacencyList[sourceIndex]->city, adjacencyList[destinationIndex]->city);
        printShortestPath(adjacencyList, count, previous, destinationIndex, mode);

        // Print the total distance
        printf("\nTotal distance: %d km\n", distance[destinationIndex]);
    }
    fclose(fp);

    // Clean up the allocated memory
    free(distance);
    free(visited);
    free(previous);
}
