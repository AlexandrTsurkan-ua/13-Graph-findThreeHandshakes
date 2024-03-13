#pragma once
#include <string>



#ifndef __GRAPH__
#define __GRAPH__

#define SIZE 10
#define VERYBIGINT 1000000000


class Graph
{
public:
	Graph();

	void addVertex(int vnumber, std::string _name);
	void addEdge(int v1, int v2, int weight = 1);
	void width(int start);
	int findPathCount(int from, int to);
	void findPathCountInner(int from, int to, bool visited[], int& PathCount);
	int findMinWayDFS(int v1, int v2);
	void inner(int current, int to, bool visited[], int& PathCount, int& min, int& currentDistance);
	void findThreeHandshakes();

	int dummy1(int v1, int v2);
	void dummy2(void** param);

	int GetWeight(int v1, int v2);

private:

	bool are_adj(int v1, int v2);
	bool vertexExists(int v);


	int matrix[SIZE][SIZE];

	int vertexes[SIZE];

	std::string name[SIZE];

	int vertexCount;

};



#endif

