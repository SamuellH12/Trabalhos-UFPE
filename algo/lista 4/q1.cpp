#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

struct Node
{
    int val;
    Node* next = NULL;

    Node(int val) : val(val) {}
};

template<typename T>    
class lista {

    private:

    int sz = 0;
    Node* head = NULL;    

    public:

    Node* begin(){ return head; }

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

const int MAXN = 1e5;

lista<int> grafo[MAXN];
bool vis[MAXN];

void dfs(int u)
{
    vis[u] = true;
    cout << u << " ";

    auto it = grafo[u].begin();

    while(it != NULL)
    {
        auto v = it->val;
        if(!vis[v]) dfs(v);
        it = it->next;
    }
}


int main(){

    int n; cin >> n;

    int u, v, s;

    do {   
        cin >> u >> v >> s;

        grafo[u].push(v);
        grafo[v].push(u);

    } while(s != 0);


    for(int i=0; i<n; i++)
    {
        cout << i << ": ";

        if(grafo[i].empty())
        {
            cout << "Lista Vazia" << endl;
            continue;
        }

        auto it = grafo[i].begin();

        while(it != NULL)
        {
            cout << it->val << " ";
            it = it->next;
        }

        cout << endl;
    }

    cout << endl;
    dfs(0);

    return 0;
}