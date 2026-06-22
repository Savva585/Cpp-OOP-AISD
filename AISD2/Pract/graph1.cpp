#include <iostream>
#include <unordered_set>
using namespace std;
struct Edge
{
    int to;
    int distance;
    Edge *next;
};

struct Node
{
    int id;
    Edge *edges;
};

int countLoops(Node *graph, int size)
{
    if (!graph || size == 0)
        return 0;
    int cnt = 0;
    for (int i = 0; i < size; ++i)
    {
        Edge *cur = graph[i].edges;
        while (cur)
        {
            if (cur->to == i)
            {
                cnt++;
            }
            cur = cur->next;
        }
    }
    return cnt;
}

Node *createGraph(int n)
{
    if (n <= 0)
        return nullptr;
    Node *graph = new Node[n];
    for (int i = 0; i < n; ++i)
    {
        graph[i].id = i;
        graph[i].edges = nullptr;
    }
    return graph;
}

void addEdge(Node *graph, int from, int to, int dist)
{
    Edge *new_edge = new Edge;
    new_edge->distance = dist;
    new_edge->to = to;
    new_edge->next = graph[from].edges;
    graph[from].edges = new_edge;
}

void printGraph(const Node *graph, int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << graph[i].id << ": ";
        Edge *cur = graph[i].edges;
        while (cur)
        {
            cout << "(" << cur->to << ", " << cur->distance << ")";
            if (cur->next)
                cout << " -> ";
            cur = cur->next;
        }
        cout << "\n";
    }
}

bool hasEdge(const Node *graph, int from, int to)
{
    if (!graph[from].edges)
        return false;
    Edge *cur = graph[from].edges;
    while (cur)
    {
        if (cur->to == to)
            return true;
        cur = cur->next;
    }
    return false;
}

int getEdgeWeight(const Node *graph, int from, int to)
{
    if (!graph[from].edges)
        return -1;
    Edge *cur = graph[from].edges;
    while (cur)
    {
        if (cur->to == to)
            return cur->distance;
        cur = cur->next;
    }
    return -1;
}

int outDegree(const Node *graph, int vertex)
{
    if (!graph[vertex].edges)
        return 0;
    Edge *cur = graph[vertex].edges;
    int cnt = 0;
    while (cur)
    {
        cnt++;
        cur = cur->next;
    }
    return cnt;
}

void removeNode(Node *&graph, int &n, int vertex)
{
    if (vertex < 0 || vertex >= n)
        return;

    Edge *cur = graph[vertex].edges;
    while (cur)
    {
        Edge *deleter = cur;
        cur = cur->next;
        delete deleter;
    }

    for (int i = 0; i < n; ++i)
    {
        if (i == vertex)
            continue;

        Edge *prev = nullptr;
        Edge *cur = graph[i].edges;

        while (cur)
        {
            if (cur->to == vertex)
            {
                if (prev)
                {
                    prev->next = cur->next;
                }
                else
                {
                    graph[i].edges = cur->next;
                }
                Edge *deleter = cur;
                cur = cur->next;
                delete deleter;
            }
            else
            {
                if (cur->to > vertex)
                {
                    cur->to--;
                }
                prev = cur;
                cur = cur->next;
            }
        }
    }

    for (int i = vertex; i < n - 1; ++i)
    {
        graph[i] = graph[i + 1];
    }
    n--;
}

void removeEdge(Node *graph, int from, int to)
{
    if (!graph[from].edges)
        return;
    Edge *cur = graph[from].edges;
    if (cur->to == to)
    {
        Edge *tmp = cur->next;
        graph[from].edges = tmp;
        delete cur;
        return;
    }
    while (cur->next)
    {
        if (cur->next->to == to)
        {
            Edge *cmp = cur->next->next;
            Edge *deleter = cur->next;
            cur->next = cmp;
            delete deleter;
            return;
        }
        cur = cur->next;
    }
    return;
}

void removeEdge(Node *graph, int from, int to)
{
    if (!graph[from].edges)
        return;
    Edge *cur = graph[from].edges;
    Edge *prev = nullptr;
    while (cur)
    {
        if (cur->to == to)
        {
            if (prev)
            {
                prev->next = cur->next;
                delete cur;
                cur = prev->next;
            }
            else
            {
                graph[from].edges = cur->next;
                cur = cur->next;
            }
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }
    return;
}

int inDegree(const Node *graph, int to, int n)
{
    if (!graph)
        return -1;
    int cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        if (i == to)
            continue;
        Edge *cur = graph[i].edges;
        while (cur)
        {
            if (cur->to == to)
                cnt++;
            cur = cur->next;
        }
    }
    return cnt;
}

int *getNeighbors(const Node *graph, int vertex, int *size)
{
    int cnt = 0;
    Edge *cur = graph[vertex].edges;
    while (cur)
    {
        cnt++;
        cur = cur->next;
    }
    *size = cnt;
    if (cnt == 0)
    {
        return nullptr;
    }

    int *result = new int[cnt];
    cur = graph[vertex].edges;
    for (int i = 0; i < cnt; ++i)
    {
        result[i] = cur->to;
        cur = cur->next;
    }
    return result;
}

int *findVerticesWithLoops(const Node *graph, int n, int *returnSize)
{
    int cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        Edge *cur = graph[i].edges;
        while (cur)
        {
            if (cur->to == i)
                cnt++;
            cur = cur->next;
        }
    }
    *returnSize = cnt;
    if (cnt == 0)
        return nullptr;
    int *result = new int[*returnSize];
    cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        Edge *cur = graph[i].edges;
        while (cur)
        {
            if (cur->to == i)
            {
                result[cnt] = cur->to;
                cnt++;
            }
            cur = cur->next;
        }
    }
    return result;
}

bool findLoops(const Node *graph, int n)
{
    for (int i = 0; i < n; i++)
    {
        Edge *cur = graph[i].edges;
        while (cur)
        {
            if (cur->to == i)
            {
                return true;
            }
            cur = cur->next;
        }
    }
    return false;
}

bool hasMultipleEdges(const Node *graph, int n)
{
    if (!graph)
        return false;

    for (int i = 0; i < n; ++i)
    {
        Edge *outer = graph[i].edges;

        while (outer)
        {
            Edge *inner = outer->next;
            while (inner)
            {
                if (outer->to == inner->to)
                {
                    return true;
                }
                inner = inner->next;
            }
            outer = outer->next;
        }
    }

    return false;
}

int *findSinks(const Node *graph, int n, int *returnSize)
{
    int cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        Edge *cur = graph[i].edges;
        if (!cur)
            cnt++;
    }
    *returnSize = cnt;
    if (cnt == 0)
        return nullptr;
    int *result = new int[*returnSize];
    cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        Edge *cur = graph[i].edges;
        if (!cur)
        {
            result[cnt] = graph[i].id;
            cnt++;
        }
    }
    return result;
}

int findCommonNeighbor(const Node *graph, int a, int b, int n)
{
    if (!graph[a].edges || !graph[b].edges)
        return -1;
    Edge *cur1 = graph[a].edges;
    while (cur1)
    {
        Edge *cur2 = graph[b].edges;
        while (cur2)
        {
            if (cur1->to == cur2->to)
                return cur1->to;
            cur2 = cur2->next;
        }
        cur1 = cur1->next;
    }
    return -1;
}

void removeMultipleEdges(Node *graph, int n)
{
    if (!graph)
        return;

    for (int i = 0; i < n; ++i)
    {
        Edge *outer = graph[i].edges;

        while (outer)
        {
            Edge *prev = outer;
            Edge *inner = outer->next;

            while (inner)
            {
                if (inner->to == outer->to)
                {
                    prev->next = inner->next;
                    delete inner;
                    inner = prev->next;
                }
                else
                {
                    prev = inner;
                    inner = inner->next;
                }
            }
            outer = outer->next;
        }
    }
}

int sumDistances(Node *graph, int size)
{
    if (!graph || size == 0)
        return 0;
    int sum = 0;
    for (int i = 0; i < size; ++i)
    {
        Edge *cur = graph[i].edges;
        while (cur)
        {
            sum += cur->distance;
            cur = cur->next;
        }
    }
    return sum;
}

void removeEdgesWithDistance(Node *graph, int size, int dist)
{
    if (!graph || size == 0)
        return;

    for (int i = 0; i < size; ++i)
    {
        Edge *cur = graph[i].edges;
        Edge *prev = nullptr;

        while (cur)
        {
            if (cur->distance == dist)
            {
                if (prev)
                {
                    prev->next = cur->next;
                }
                else
                {
                    graph[i].edges = cur->next;
                }
                Edge *buf = cur;
                cur = cur->next;
                delete buf;
            }
            else
            {
                prev = cur;
                cur = cur->next;
            }
        }
    }
}

int maxSumVertex(Node *graph, int size)
{
    if (!graph || size == 0)
        return 0;
    int sum = INT_MIN;
    int maybe = 0;
    for (int i = 0; i < size; ++i)
    {
        int cur_sum=0;
        Edge *cur = graph[i].edges;
        while(cur){
            cur_sum+=cur->distance;
            cur=cur->next;
        }
        if(sum<cur_sum){
            sum=cur_sum;
            maybe=graph[i].id;
        }
    }
    return maybe;
}

double averageDistance(Node* graph, int size){
    if(!graph || size==0) return 0;
    int cnt=0;
    int sum=0;
    for(int i=0;i<size;++i){
        Edge* cur=graph[i].edges;
        while(cur){
            sum+=cur->distance;
            cnt++;
            cur=cur->next;
        }
    }
    return cnt? (double)sum/cnt : 0;
}