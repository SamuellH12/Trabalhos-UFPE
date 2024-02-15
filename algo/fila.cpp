#include <bits/stdc++.h>

template<typename T>    
class fila {

    private:

    struct Node
    {
        T val;
        Node* next = NULL;

        Node(T val) : val(val) {}
    };


    int sz = 0;
    Node* head = NULL;
    Node* tail = NULL;

    public:

    T front(){ return head->val; }
    T back() { return tail->val; }

    T pop()
    {
        Node* old = head;

        head = head->next;

        if(head == NULL) tail = NULL;

        sz--;
        T val = old->val;
        free(old);

        return val;
    }

    void push(T x)
    {
        Node* nw = new Node(x);
        
        if(head == NULL) head = nw;
        if(tail) tail->next = nw;
        
        tail = nw;

        sz++;
    }

    int size(){ return sz; }
    bool empty(){ return !sz; }
};
