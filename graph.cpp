#include <iostream>
#include "graph.h"


Graph::Graph() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            matrix[i][j] = 0;
    vertexCount = 0;
}

// ���������� �������
void Graph::addVertex(int vnumber, std::string _name)
{
    vertexes[vertexCount] = vnumber;
    name[vertexCount] = _name;
    vertexCount++;

}

// ���������� �����
void Graph::addEdge(int v1, int v2, int weight)
{
    matrix[v1][v2] = weight;
    matrix[v2][v1] = weight;
}


bool Graph::are_adj(int v1, int v2)
{
    return matrix[v1][v2] != 0;
}


// �������� ������������� �������
bool Graph::vertexExists(int v)
{
    for (int i = 0; i < vertexCount; i++)
        if (vertexes[i] == v)
            return true;
    return false;
}



void Graph::width(int start)
{
    int queue_to_visit[SIZE]; // ������/������� ������ ��� ������
    int queueCount = 0; // �� ������� - ���-�� ������ � �������/������� ��� ������

    bool visited[SIZE]; // ������ ���������� ������
    for (int i = 0; i < SIZE; i++)
        visited[i] = false; // �������������� ��� ���������� ��� ����

    queue_to_visit[queueCount++] = start; // ������ � ������� ��������� �������
    while (queueCount > 0) // ���� ���� ������� ������� ������ 0
    {
        // ������ �� ������� ������� -- ��������� ������� ������� ���, ������� ������ � �������
        int current = queue_to_visit[0];
        queueCount--; // ��������� ������� �� 1, �.�. ��� �� ������� ������� � �������
        for (int i = 0; i < queueCount; i++)
        {
            queue_to_visit[i] = queue_to_visit[i + 1]; // ��� ��� �� �������� ���� ������/������� �����, �.�. 2-� ���������� 1-�, ������ ������, � �.�.
        }
        visited[current] = true; // �������� ������� ������� ��� ����������
        std::cout << "v" << current << " -> "; // ������� �� �� �����
        // ����� ������� ������ � ���������� �� � �������
        for (int i = 0; i < SIZE; i++)
        {
            bool alreadyAdded = false;
            for (int j = 0; j < queueCount; j++) // �������� ������ �� �������� �� �������� � �������
            {
                if (queue_to_visit[j] == i)
                {
                    alreadyAdded = true;
                    break;
                }
            }
            // ���� ��� �� ��������, ���� ��� �� ��������, � ���� ���� ����� ����� ������� �������� � �������� i �� �����
            if (!alreadyAdded && are_adj(current, i) && !visited[i])
            {
                queue_to_visit[queueCount++] = i; // ���� ��� �����������, �������� � ����� ������� � ����������� ������� ������� �� 1
            }

        }
    }
    std::cout << std::endl;
}



int Graph::findPathCount(int from, int to)
{
    int PathCount = 0;
    bool visited[SIZE]; // ������ ���������� ������
    for (int i = 0; i < SIZE; i++)
    {
        visited[i] = false; // �������������� ��� ������������
    }

    findPathCountInner(from, to, visited, PathCount);
    return PathCount;
}


void Graph::findPathCountInner(int from, int to, bool visited[], int& PathCount)
{
    visited[from] = true; // �������� ��� ����������


    if (from == to)
    {
        PathCount++;
        visited[from] = false;
    }
    else
    {
        for (int i = 0; i < SIZE; i++)
        {
            if (are_adj(from, i) && !visited[i])
            {
                findPathCountInner(i, to, visited, PathCount);


            }

        }

    }
    visited[from] = false;
}



int Graph::GetWeight(int v1, int v2)
{
    if (are_adj(v1, v2))
    {
        return matrix[v1][v2];
    }
    else
    {
        return 0;
    }
}



int Graph::findMinWayDFS(int from, int to)
{
    int PathCount = 0;
    int min = VERYBIGINT;
    int currentDistance = 0;
    bool visited[SIZE]; // ������ ���������� ������
    for (int i = 0; i < SIZE; i++)
    {
        visited[i] = false; // �������������� ��� ������������
    }

    inner(from, to, visited, PathCount, min, currentDistance);
    return min;
}

void Graph::inner(int from, int to, bool visited[], int& PathCount, int& min, int& currentDistance)
{
    visited[from] = true; // �������� ��� ����������


    if (from == to)
    {
        PathCount++;
        visited[from] = false;
        if (currentDistance <= min)
        {
            min = currentDistance;
            //currentDistance = 0;
        }

    }
    else
    {
        for (int i = 0; i < SIZE; i++)
        {
            if (are_adj(from, i) && !visited[i])
            {
                currentDistance = currentDistance + GetWeight(from, i);
                // std::cout << currentDistance << std::endl;
                inner(i, to, visited, PathCount, min, currentDistance);

            }

        }

    }
    visited[from] = false;
}


void Graph::findThreeHandshakes()
{
    int weights[SIZE][SIZE]; // ������� �����
    // ������������ �������
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (i == j)
            {
                weights[i][j] = 0; // ���� �� ����� ���� ����� 0
            }
            else {
                if (!are_adj(i, j))
                {
                    weights[i][j] = VERYBIGINT; // ���� ����� ���
                }
                else {
                    weights[i][j] = matrix[i][j]; // ���� ����� ����
                }
            }
        }
    }

    for (int k = 0; k < vertexCount; k++) // �������� �� k
    {
        int ck = vertexes[k]; // ������� ����� �������
        for (int i = 0; i < vertexCount; i++)
        {
            if (i == k)
                continue;
            int ci = vertexes[i];
            for (int j = 0; j < vertexCount; j++)
            {
                if (j == k)
                    continue;
                int cj = vertexes[j];
                if (weights[ci][ck] + weights[ck][cj] < weights[ci][cj]) {
                    // �������� ������� �����
                    weights[ci][cj] = weights[ci][ck] + weights[ck][cj];
                }
            }
        }
    }

    for (int i = 0; i < vertexCount; i++)
    {
        int z = 0;
        std::cout << "Man " << name[i] << " is friends with: ";
        for (int j = 0; j < vertexCount; j++)
        {
            if (i == j || weights[vertexes[i]][vertexes[j]] == 0)
            {
                continue;
            }
            else if (weights[vertexes[i]][vertexes[j]] <= 3)
            {
                std::cout << name[j] << ", ";
                z++;
                // std::cout << "Man " << name[i] << " is friends with: " << name[j] << ", ";
            }
        }
        if (z == 0)
        {
            std::cout << "with anyone";
        }
        std::cout << std::endl;
    }
}