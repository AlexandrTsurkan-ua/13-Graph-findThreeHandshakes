#include <iostream>
#include "graph.h"


Graph::Graph() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            matrix[i][j] = 0;
    vertexCount = 0;
}

// добавление вершины
void Graph::addVertex(int vnumber, std::string _name)
{
    vertexes[vertexCount] = vnumber;
    name[vertexCount] = _name;
    vertexCount++;

}

// добавление ребра
void Graph::addEdge(int v1, int v2, int weight)
{
    matrix[v1][v2] = weight;
    matrix[v2][v1] = weight;
}


bool Graph::are_adj(int v1, int v2)
{
    return matrix[v1][v2] != 0;
}


// проверка существования вершины
bool Graph::vertexExists(int v)
{
    for (int i = 0; i < vertexCount; i++)
        if (vertexes[i] == v)
            return true;
    return false;
}



void Graph::width(int start)
{
    int queue_to_visit[SIZE]; // массив/очередь вершин для обхода
    int queueCount = 0; // ее счетчик - кол-во вершин в очереди/массиве для обхода

    bool visited[SIZE]; // список посещенных вершин
    for (int i = 0; i < SIZE; i++)
        visited[i] = false; // инициализируем все изначально как ложь

    queue_to_visit[queueCount++] = start; // кладем в очередь начальную вершину
    while (queueCount > 0) // цикл пока счетчик очереди больше 0
    {
        // взятие из очереди вершины -- назначаем текущую вершину той, которая первая в очереди
        int current = queue_to_visit[0];
        queueCount--; // уменьшаем счетчик на 1, т.е. как бы удаляем вершину с очереди
        for (int i = 0; i < queueCount; i++)
        {
            queue_to_visit[i] = queue_to_visit[i + 1]; // тут как бы сдвигаем весь массив/очередь влево, т.е. 2-я становится 1-й, третья второй, и т.д.
        }
        visited[current] = true; // отмечаем текущую вершину как посещенную
        std::cout << "v" << current << " -> "; // выводим ее на экран
        // поиск смежных вершин и добавление их в очередь
        for (int i = 0; i < SIZE; i++)
        {
            bool alreadyAdded = false;
            for (int j = 0; j < queueCount; j++) // проверка циклом не помещена ли ввершина в очередь
            {
                if (queue_to_visit[j] == i)
                {
                    alreadyAdded = true;
                    break;
                }
            }
            // если еще не помещена, если еще не посещена, и если есть ребро между текущей вершиной и вершиной i по циклу
            if (!alreadyAdded && are_adj(current, i) && !visited[i])
            {
                queue_to_visit[queueCount++] = i; // если все выполняется, помещаем в конец очереди и увеличиваем счетчик очереди на 1
            }

        }
    }
    std::cout << std::endl;
}



int Graph::findPathCount(int from, int to)
{
    int PathCount = 0;
    bool visited[SIZE]; // список посещенных вершин
    for (int i = 0; i < SIZE; i++)
    {
        visited[i] = false; // инициализируем как непосещенные
    }

    findPathCountInner(from, to, visited, PathCount);
    return PathCount;
}


void Graph::findPathCountInner(int from, int to, bool visited[], int& PathCount)
{
    visited[from] = true; // помечаем как посещенную


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
    bool visited[SIZE]; // список посещенных вершин
    for (int i = 0; i < SIZE; i++)
    {
        visited[i] = false; // инициализируем как непосещенные
    }

    inner(from, to, visited, PathCount, min, currentDistance);
    return min;
}

void Graph::inner(int from, int to, bool visited[], int& PathCount, int& min, int& currentDistance)
{
    visited[from] = true; // помечаем как посещенную


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
    int weights[SIZE][SIZE]; // матрица путей
    // инициализаци матрицы
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (i == j)
            {
                weights[i][j] = 0; // путь до самой себя равен 0
            }
            else {
                if (!are_adj(i, j))
                {
                    weights[i][j] = VERYBIGINT; // если ребра нет
                }
                else {
                    weights[i][j] = matrix[i][j]; // если ребро есть
                }
            }
        }
    }

    for (int k = 0; k < vertexCount; k++) // итерации по k
    {
        int ck = vertexes[k]; // возьмем номер вершины
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
                    // пересчет матрицы путей
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