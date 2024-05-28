#pragma once
#include "stdio.h"
#include "stdlib.h"

enum Side
{
    LEFT = 'L',
    RIGHT = 'R',
    NONE = '_'
};


struct element
{
    int key;
    int vertexDegree;
    int *neighbours;
    bool visited=false;
    Side side = NONE;
    int greedyColor = 0;
    int LFColor = 0;
};

class Graph
{
    int n;
    int nmbOfEdges;
    int nmbOfComponents; //składowe spójności
    int nmbOfCycle4;
    element *vertices;
    element **deegreSortedVertices;
    bool bipartiness;
    void reversedHeapSort(int *arr, int n);
    void heapify(int *arr, int n, int i);
    void swap(int *a, int *b);
    // void BFS(int v);
    long long int complementsEdges();
    void DFS(int v);
    void recDFS(int v);
    void bipartite();
    void greedyColoring();
    void printGreedyColors();
    void printBool(bool a);
    void LFColoring();
    void sortVerticesByDegree();
    void heapifyVertices(int n, int i);
    void swap(element *a, element *b);
    void printLFColors();
public:
    Graph();
    void createDeegreSequence();
    void printGraph();
    void print();
    bool checkIfGraphIsConnected();
    bool checkIfAllVerticesVisited();
    void countNmbOfComponents();
    ~Graph();
};