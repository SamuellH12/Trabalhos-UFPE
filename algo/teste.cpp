#include <bits/stdc++.h>
using namespace std;

template<typename T>    
class pilha {

    private:

    struct Node
    {
        T val;
        Node* next = NULL;

        Node(T val) : val(val) {}
    };

    int sz = 0;
    Node* head = NULL;    

    public:

    T top(){ return head->val; }

    T pop()
    {
        Node* old = head;

        head = old->next;
        sz--;

        return old->val;
    }

    void push(T x)
    {
        Node* nw = new Node(x);
        
        nw->next = head;
        head = nw;
        
        sz++;
    }

    int size(){ return sz; }

    bool empty(){ return !sz; }
};

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

        return old->val;
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

int main(){

    int op;
    string x;

    pilha<string> p;

    cout << "---------PILHA-----------" << endl;
    while(cin >> op && ~op)
    {
        if(op == 1) cin >> x, p.push(x);
        if(op == 2) cout << "Top: " << p.top() << endl;
        if(op == 3) cout << "Siz: " << p.size() << endl;
        if(op == 4) cout << "Emp? " << p.empty() << endl;
        if(op == 5) cout << "Pop " << p.pop() << endl;
    }

    fila<string> f;
    cout << "---------FILA-----------" << endl;
    while(cin >> op && ~op)
    {
        if(op == 1) cin >> x, f.push(x);
        if(op == 2) cout << "Frnt: " << f.front() << endl;
        if(op == 2) cout << "back: " << f.back() << endl;
        if(op == 3) cout << "Siz: "  << f.size() << endl;
        if(op == 4) cout << "Emp? "  << f.empty() << endl;
        if(op == 5) cout << "Pop  "  << f.pop() << endl;
    }

    return 0;
}