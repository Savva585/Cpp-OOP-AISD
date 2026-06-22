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
    Node *next;
};

int countLoops(Node *head)
{
    if (!head)
        return 0;
    Node *current = head;
    int cnt = 0;
    while (current)
    {
        Edge *cur = current->edges;
        while (cur)
        {
            if (cur->to == current->id)
                cnt++;
            cur = cur->next;
        }
        current = current->next;
    }
    return cnt;
}

bool hasEdge(Node *head, int from, int to)
{
    Node *current = head;
    while (current)
    {
        if (current->id == from)
        {
            Edge *cur = current->edges;
            while (cur)
            {
                if (cur->to == to)
                    return true;
                cur = cur->next;
            }
            return false;
        }
        current = current->next;
    }
    return false;
}

int getEdgeWeight(Node *head, int from, int to)
{
    Node *current = head;
    while (current)
    {
        if (current->id == from)
        {
            Edge *cur = current->edges;
            while (cur)
            {
                if (cur->to == to)
                    return cur->distance;
                cur = cur->next;
            }
            return -1;
        }
        return -1;
    }
}

void removeEdge(Node *head, int from, int to)
{
    Node *current = head;
    while (current)
    {
        if (current->id == from)
        {
            Edge *cur = current->edges;
            if (!cur)
                return;
            if (cur->to == to)
            {
                Edge *tmp = cur->next;
                current->edges = tmp;
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
        }
        current = current->next;
    }
    return;
}

int removeAllLoops(Node *head)
{
    Node *current = head;
    int cnt = 0;

    while (current)
    {
        while (current->edges && current->edges->to == current->id)
        {
            Edge *tmp = current->edges->next;
            delete current->edges;
            current->edges = tmp;
            cnt++;
        }

        if (!current->edges)
        {
            current = current->next;
            continue;
        }

        Edge *cur = current->edges;
        while (cur->next)
        {
            if (cur->next->to == current->id)
            {
                Edge *deleter = cur->next;
                cur->next = cur->next->next;
                delete deleter;
                cnt++;
            }
            else
            {
                cur = cur->next;
            }
        }

        current = current->next;
    }

    return cnt;
}
