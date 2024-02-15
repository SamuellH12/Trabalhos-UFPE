#include <iostream>
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

        head = head->next;
        sz--;

        T val = old->val;
        free(old);

        return val;
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


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int t; cin >> t;

    for(int cnt=1; cnt<=t; cnt++)
    {
        pilha<int> p; 

        int at; 

        while(cin >> at && at)
        {
            while(!p.empty() && (p.top()&1) == (at&1)) at = abs(p.pop()-at);
            
            p.push(at);
        }

        cout << "Pilha " << cnt << ": " << p.size() << " " << (p.empty() ? -1 : p.top()) << endl;
    }

    return 0;
}