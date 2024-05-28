#include "Graph.hpp"

Graph::Graph()
{
    nmbOfCycle4 = 0;
    nmbOfEdges = 0;
    bipartiness = false;
    scanf("%d", &n);
    vertices = new element[n];
    deegreSortedVertices = new element*[n];
    for (int i = 0; i < n; i++)
    {
        vertices[i].key = i + 1;
        scanf("%d", &vertices[i].vertexDegree);
        vertices[i].neighbours = (int *)malloc(sizeof(int) * vertices[i].vertexDegree);
        
        for (int j = 0; j < vertices[i].vertexDegree; j++)
        {
            scanf("%d", &vertices[i].neighbours[j]);
            nmbOfEdges++;
        }
        deegreSortedVertices[i] = &vertices[i];
    }
    nmbOfEdges /= 2;
    countNmbOfComponents();
    bipartite();
    greedyColoring();
    // LFColoring();
}

void Graph::printGraph()
{
    printf("Graph with %d vertices\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("Vertex %d with degree %d\n", vertices[i].key, vertices[i].vertexDegree);
        for (int j = 0; j < vertices[i].vertexDegree; j++)
        {
            printf("Neighbour %d\n", vertices[i].neighbours[j]);
        }
    }
}

void Graph::print()
{
    createDeegreSequence();          // 1
    printf("%d\n", nmbOfComponents); // 2
    printBool(bipartiness);          //  3 printf("?\n");
    printf("?\n");                   // 4
    printf("?\n");                   // 5
    printGreedyColors();             // 6a //printf("?\n");
     printf("?\n"); //printLFColors();                  // 6b
    printf("?\n");                   // 6c
    printf("?\n");                   // 7
    complementsEdges(); // printf("?\n"); // 8

   
}

void Graph::createDeegreSequence()
{
    int *degreeSequence = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        degreeSequence[i] = vertices[i].vertexDegree;
    }
    reversedHeapSort(degreeSequence, n);
    for (int i = n - 1; i >= 0; i--)
    {
        printf("%d ", degreeSequence[i]);
    }

    printf("\n");
    free(degreeSequence);
}



void Graph::reversedHeapSort(int *arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void Graph::heapify(int *arr, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest])
    {
        largest = l;
    }
    if (r < n && arr[r] > arr[largest])
    {
        largest = r;
    }
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void Graph::swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

Graph::~Graph()
{
    for (int i = 0; i < n; i++)
    {
        free(vertices[i].neighbours);
    }
    delete[] vertices;
}



void Graph::recDFS(int v)
{
    vertices[v].visited = true;
    for (int i = 0; i < vertices[v].vertexDegree; i++)
    {
        if (!vertices[vertices[v].neighbours[i] - 1].visited)
        {
            DFS(vertices[v].neighbours[i] - 1);
        }
    }
}

void Graph::DFS(int v)
{
    int stackSize = vertices[v].vertexDegree * n*2;
    int *stack = new int[stackSize]; 
    int stackTop = 0;
   
    stack[stackTop++] = v;

    while (stackTop != 0)
    {
        v = stack[--stackTop];

        if (!vertices[v].visited)
        {
            vertices[v].visited = true;

            for (int i = 0; i < vertices[v].vertexDegree; i++)
            {
                
                if (!vertices[vertices[v].neighbours[i] - 1].visited)
                {
                    stack[stackTop++] = vertices[v].neighbours[i] - 1;
                }
            }
        }
    }

    delete[] stack;
}

void Graph::countNmbOfComponents() //gdy bedzie problem z czasem połączyć to z  bipartiite
{
    nmbOfComponents = 0;

    for (int i = 0; i < n; i++)
    {
        // if (vertices[i].side == NONE)
        // {
        //     vertices[i].side = LEFT;
        // }
        if (!vertices[i].visited)
        {
            DFS(i);
            nmbOfComponents++;
        }
    }
}

bool Graph::checkIfAllVerticesVisited()
{
    for (int i = 0; i < n; i++)
    {
        if (!vertices[i].visited)
        {
            return false;
        }
    }
    return true;
}

long long int Graph::complementsEdges()
{
    long long int maxEdges = (long long int)n * (long long int)(n - 1) / 2;
    printf("%lld\n", maxEdges - (long long int)nmbOfEdges);
    return maxEdges - nmbOfEdges;
}


void Graph::bipartite()
{
    for (int i = 0; i < n; i++)
    {
        if (vertices[i].side == NONE)
        {
            vertices[i].side = LEFT;
            int stackSize = vertices[i].vertexDegree * n*2;
            int *stack = new int[stackSize]; 
            int stackTop = 0;
            stack[stackTop++] = i;

            while (stackTop != 0)
            {
                int v = stack[--stackTop];
                for (int j = 0; j < vertices[v].vertexDegree; j++)
                {
                    if (vertices[vertices[v].neighbours[j] - 1].side == NONE)
                    {
                        vertices[vertices[v].neighbours[j] - 1].side = (vertices[v].side == LEFT) ? RIGHT : LEFT;
                        stack[stackTop++] = vertices[v].neighbours[j] - 1;
                    }
                    else if (vertices[vertices[v].neighbours[j] - 1].side == vertices[v].side)
                    {
                        bipartiness = false;
                        delete[] stack;
                        return;
                    }
                }
            }
            delete[] stack;
        }
    }
   
    bipartiness = true;
    
}


void Graph::greedyColoring()
{
    
    for (int i = 0; i < n; i++)
    {
        vertices[i].greedyColor = 1;
        for (int j = 0; j < vertices[i].vertexDegree; j++)
        {
            if (vertices[vertices[i].neighbours[j] - 1].greedyColor == vertices[i].greedyColor)
            {
                vertices[i].greedyColor++;
                j = -1;
            }
        }
    }
}

void Graph::sortVerticesByDegree()
{
    element *temp;
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            if (deegreSortedVertices[i]->vertexDegree > deegreSortedVertices[j]->vertexDegree)
            {
                temp = deegreSortedVertices[i];
                deegreSortedVertices[i] = deegreSortedVertices[j];
                deegreSortedVertices[j] = temp;
            }
        }
    }
}

void Graph::swap(element *a, element *b)
{
    element temp = *a;
    *a = *b;
    *b = temp;
}

void Graph::heapifyVertices(int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && deegreSortedVertices[l]->vertexDegree > deegreSortedVertices[largest]->vertexDegree)
    {
        largest = l;
    }
    if (r < n && deegreSortedVertices[r]->vertexDegree > deegreSortedVertices[largest]->vertexDegree)
    {
        largest = r;
    }
    if (largest != i)
    {
        // swap(&deegreSortedVertices[i], &deegreSortedVertices[largest]);
        heapifyVertices(n, largest);
    }
}

void Graph::LFColoring()
{
    sortVerticesByDegree();
    for (int i=0;i<n;i++)
    {
        deegreSortedVertices[i]->LFColor = 1;
        for (int j=0;j<deegreSortedVertices[i]->vertexDegree;j++)
        {
            if (deegreSortedVertices[deegreSortedVertices[i]->neighbours[j]-1]->LFColor == deegreSortedVertices[i]->LFColor)
            {
                deegreSortedVertices[i]->LFColor++;
                j=-1;
            }
        }
    }
}
void Graph::printGreedyColors()
{
    for (int i=0; i<n; i++)
    {
        printf("%d ", vertices[i].greedyColor);
    }
    printf("\n");
}

void Graph::printBool(bool a)
{
    if (a)
    printf("T\n");
    else
    printf("F\n");
}

void Graph::printLFColors()
{
    for (int i=0; i<n; i++)
    {
        printf("%d ", deegreSortedVertices[i]->LFColor);
    }
    printf("\n");
}