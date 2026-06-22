struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *reverseList(ListNode *head)
{
    if (!head || !head->next)
        return head;

    ListNode *prev = nullptr;
    ListNode *curr = head;
    ListNode *next = nullptr;

    while (curr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

ListNode *removeNthFromEnd(ListNode *head, int n)
{
    if (!head || n <= 0)
        return head;

    ListNode *dummy = new ListNode(0);
    dummy->next = head;

    ListNode *fast = dummy;
    ListNode *slow = dummy;

    for (int i = 0; i <= n; ++i)
    {
        if (!fast)
        {
            delete dummy;
            return head;
        }
        fast = fast->next;
    }

    while (fast)
    {
        fast = fast->next;
        slow = slow->next;
    }
    ListNode *toDelete = slow->next;
    slow->next = slow->next->next;
    delete toDelete;

    ListNode *result = dummy->next;
    delete dummy;

    return result;
}

ListNode *insertSorted(ListNode *head, int val)
{
    if (!head)
    {
        ListNode *buf = new ListNode(val);
        return buf;
    }
    if (head->val > val)
    {
        ListNode *buf = new ListNode(val);
        buf->next = head;
        return buf;
    }
    ListNode *cur = head;
    while (cur->next)
    {
        if (val < cur->next->val)
        {
            ListNode *buf = new ListNode(val);
            buf->next = cur->next;
            cur->next = buf;
            return head;
        }
        cur = cur->next;
    }
    ListNode *buf = new ListNode(val);
    cur->next = buf;
    return head;
}

ListNode *deleteHeadSingly(ListNode *head)
{
    if (!head)
        return head;
    if (!head->next)
    {
        delete head;
        return nullptr;
    }
    ListNode *buf = head;
    head = head->next;
    delete buf;
    return head;
}

ListNode *deleteTailSingly(ListNode *head)
{
    if (!head)
        return head;
    if (!head->next)
    {
        delete head;
        return nullptr;
    }
    ListNode *new_tail = head;
    while (new_tail->next->next)
    {
        new_tail = new_tail->next;
    }
    ListNode *tail = new_tail->next;
    new_tail->next = nullptr;
    delete tail;
    return head;
}

ListNode *insertTailSingly(ListNode *head, int val)
{
    if (!head)
    {
        ListNode *buf = new ListNode(val);
        return head = buf;
    }
    ListNode *cur = head;
    while (cur->next)
    {
        cur=cur->next;
    }
    ListNode *buf = new ListNode(val);
    cur->next=buf;
    return head;
}

ListNode *insertHeadSingly(ListNode *head, int val){
      if(!head){
        ListNode* buf= new ListNode(val);
        return head=buf;
      }
      ListNode* buf= new ListNode(val);
      buf->next=head;
      head=buf;
      return head;
}

// цикл

ListNode *insertAtHeadCircularSingly(ListNode *head, int val)
{
    if (!head)
    {
        ListNode *buf = new ListNode(val);
        buf->next = buf;
        return buf;
    }
    if (head->next == head)
    {
        ListNode *buf = new ListNode(val);
        buf->next = head;
        head->next = buf;
        head = buf;
        return head;
    }
    ListNode *tail = head->next;
    while (tail->next != head)
    {
        tail = tail->next;
    }
    ListNode *buf = new ListNode(val);
    buf->next = head;
    tail->next = buf;
    head = buf;
    return head;
}

ListNode *deleteHeadCircularSingly(ListNode *head)
{
    if (!head)
        return head;
    if (head->next == head)
    {
        delete head;
        return nullptr;
    }
    ListNode *tail = head->next;
    while (!(tail->next == head))
    {
        tail = tail->next;
    }
    ListNode *buf = head;
    head = head->next;
    tail->next = head;
    delete buf;
    return head;
}

ListNode *deleteTailCircularSingly(ListNode *head)
{
    if (!head)
        return head;
    if (head->next == head)
    {
        delete head;
        return nullptr;
    }
    ListNode *tail = head->next;
    ListNode *tail_new = head;
    while (tail->next != head)
    {
        tail = tail->next;
        tail_new = tail_new->next;
    }
    delete tail;
    tail_new->next = head;
    return head;
}

ListNode *findCircularSingly(ListNode *head, int val)
{
    if (!head)
        return nullptr;
    if (head->next == head && head->val != val)
        return nullptr;
    ListNode *cur = head;
    do
    {
        if (cur->val == val)
            return cur;
        cur = cur->next;
    } while (cur != head);
    return nullptr;
}

ListNode *insertAfterCircularSingly(ListNode *head, int val, int newVal)
{
    if (!head)
        return nullptr;
    if (val != head->val && head->next == head)
    {
        return nullptr;
    }
    ListNode *cur = head->next;
    while (cur->val != val)
    {
        if (cur == head)
            return nullptr;
        cur = cur->next;
    }
    ListNode *next = cur->next;
    ListNode *buf = new ListNode(newVal);
    buf->next = next;
    cur->next = buf;
    return head;
}