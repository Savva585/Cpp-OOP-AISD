struct Node
{
    int data;
    Node *prev;
    Node *next;
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

Node *createDoublyList(const int *arr, int size)
{
    if (!arr || !size)
        return nullptr;
    Node *head = new Node(arr[0]);
    Node *cur = head;
    for (int i = 1; i < size; ++i)
    {
        Node *buf = new Node(arr[i]);
        cur->next = buf;
        buf->prev = cur;
        cur = cur->next;
    }
    return head;
}

Node *insertAtHead(Node *head, int val)
{
    Node *cur = new Node(val);
    if (!head)
    {
        head = cur;
        return head;
    }
    head->prev = cur;
    cur->next = head;
    head = cur;
    return head;
}

Node *insertAtTail(Node *head, int val)
{
    Node *buf = new Node(val);
    if (!head)
    {
        head = buf;
        return head;
    }
    Node *cur = head;
    while (cur->next)
    {
        cur = cur->next;
    }
    cur->next = buf;
    buf->prev = cur;
    return head;
}

Node *insertAtIndex(Node *head, int val, int index)
{
    if (index < 0)
        return head;

    Node *buf = new Node(val);

    if (index == 0)
    {
        buf->next = head;
        if (head)
            head->prev = buf;
        return buf;
    }

    Node *cur = head;
    int cnt = 1;

    while (cur && cnt < index)
    {
        cur = cur->next;
        ++cnt;
    }

    if (!cur)
    {
        delete buf;
        return head;
    }

    buf->next = cur->next;
    buf->prev = cur;

    if (cur->next)
    {
        cur->next->prev = buf;
    }
    cur->next = buf;

    return head;
}

Node *deleteByValue(Node *head, int val)
{
    if (!head)
        return head;
    if (head->data == val)
    {
        Node *buf = head;
        head = head->next;
        delete buf;
        if (head)
        {
            head->prev = nullptr;
        }
        return head;
    }
    Node *cur = head;
    while (cur)
    {
        if (cur->data == val && !cur->next)
        {
            cur->prev->next = nullptr;
            delete cur;
            return head;
        }
        if (cur->data == val)
        {
            Node *buf = cur;
            cur->prev->next = cur->next;
            delete buf;
            return head;
        }
        cur = cur->next;
    }
    return head;
}

Node* reverseDoublyList(Node* head){
    if(!head) return head;
    Node* cur= head;
    Node* next=nullptr;
    Node* prev=nullptr;
    while(cur){
       next=cur->next;
       prev=cur->prev;
       cur->next=prev;
       cur->prev=next;
       cur=next;
    }
    head=prev->prev;
    return head;
}

bool hasDuplicates(Node* head){
    if(!head || !head->next) return false;
    Node* first =head;
    Node* second=nullptr;
    while(first){
        second=first->next;
        while(second){
            if(first->data==second->data){
                return true;
            }
            second=second->next;
        }
        first=first->next;
    }
    return false;
}


// цикл

Node* insertAtHeadCircular(Node* head, int val){
    if(!head){
        Node* buf=new Node(val);
        head=buf;
        return head;
    }
    Node* cur=new Node(val);
    Node* tail=head->prev;
    cur->next=head;
    head->prev=cur;
    cur->prev=tail;
    tail->next=cur;
    head=cur;
    return head;
}


Node* reverseCircularDoubly(Node* head){
    if(!head || head->next==head) return head;
    Node* cur= head->next;
    Node* next=nullptr;
    Node* prev=nullptr;
    while(cur!=head){
        next=cur->next;
        prev=cur->prev;
        cur->next=prev;
        cur->prev=next;
        cur=next;
    }

    Node* buf=cur->next;
    cur->next=cur->prev;
    cur->prev=buf;
    head=cur->prev;
    return head;
}


Node* findCircular(Node* head, int val){
    if(!head) return nullptr;
    if(head->next==head && head->data!=val) return nullptr;
    Node* cur=head;
    do{
        if(cur->data==val){
            return cur;
        }
      cur=cur->next;
    }while(cur!=head);
    return nullptr;
}

void swapFirstLastCircular(Node* head){
    if(!head || head->next == head) return;
    
    Node* tail = head->prev;
    int temp = head->data;
    head->data = tail->data;
    tail->data = temp;
}

