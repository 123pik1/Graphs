#include <stdio.h>
#include "Graph.hpp"


int main()
{
    int nmbOfGraphs;
    scanf("%d", &nmbOfGraphs);
    for (int i = 0; i < nmbOfGraphs; i++)
    {
        Graph g;
        g.print();
        printf("\n");
        // g.printGraph();
    }


    return 0;
}