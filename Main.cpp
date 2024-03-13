#include <iostream>
#include "graph.h"

using namespace std;



int main()
{
    Graph g;

    g.addVertex(0, "Vasya");
    g.addVertex(1, "Alex");
    g.addVertex(2, "Igor");
    g.addVertex(3, "Genry");
    g.addVertex(4, "Max");
    g.addVertex(5, "Victor");
    g.addVertex(6, "Egor");
    g.addVertex(7, "Pavel");
    g.addVertex(8, "Petr");
    g.addVertex(9, "Denis");


    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 1);
    g.addEdge(4, 5, 1);
    g.addEdge(5, 6, 1);
    g.addEdge(6, 7, 1);
    g.addEdge(7, 8, 1);
    g.addEdge(8, 9, 1);


    g.findThreeHandshakes();



    return 0;
}
