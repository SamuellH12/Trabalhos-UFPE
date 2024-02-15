#include <bits/stdc++.h>
#define endl '\n'
#define INF 0x3f3f3f3f
using namespace std;

const int MAXN = 1e5;


template<typename T>    
class Heap {

    T heap[MAXN];
    int sz = 0;

    private:
    void max_heapfy(int i){
        if(i > sz/2) return;

        int l = i*2, r = i*2+1, mx;

        if(r > sz) mx = l;
        else mx = (heap[l] > heap[r] ? l : r);

        if(heap[mx] > heap[i])
        {
            swap(heap[mx], heap[i]);
            max_heapfy(mx);
        }
    }

    void heapfy_reverse(int i)
    {
        if(!i) return;
        int l = i*2, r = i*2+1, mx = i;
         
        if(l<=sz && r <= sz) mx = (heap[l] > heap[r] ? l : r);
        else mx = (l <= sz ? l : i);

        if(heap[mx] > heap[i]) swap(heap[mx], heap[i]);

        heapfy_reverse(i>>1);
    }

    public:
    
    void push(T x)
    {
        sz++;
        heap[sz] = x;
        heapfy_reverse(sz);
    }

    T pop()
    { 
        swap(heap[1], heap[sz]);
        sz--;
        max_heapfy(1);
        return heap[sz+1];
    }

    T top(){ return heap[1]; }

    int size(){ return sz; }

    bool empty(){ return !sz; }

    void print(){
        for(int i=1; i<=sz; i++) cerr << heap[i].id << " " << heap[i].pq << " | ";
        cerr << endl;
    }

};



struct par{
    int first, second;
    par(int f, int s) : first(f), second(s) {}
    par(){ first = second = 0; }

    bool operator> (const par a){
        if(first != a.first) return first > a.first;
        return second > a.second;
    }
    bool operator< (const par a){
        if(first != a.first) return first < a.first;
        return second < a.second;
    }
};



struct Node
{
    par val;
    Node* next = NULL;

    Node(par val) : val(val) {}
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

lista<par> grafo[MAXN];
int dist[MAXN];

int n, m, e; 

int dijkstra(int source, int sink){

    for(int i=0; i<=n; i++) dist[i] = INF;

    Heap<par> pq;
    pq.push(par(0, source));
    dist[source] = 0;
    
    while(!pq.empty())
    {
        int c = -pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if(dist[u] < c) continue;
        if(u == sink) return c;
        
        auto it = grafo[u].begin();
        while(it != NULL)
        {
            auto v = it->val.first;
            auto w = it->val.second;
            // cerr << u << " -> " << v << endl;
            if(dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                pq.push(par(-dist[v], v));
            }
            // else cerr << "dist " << dist[v] << " " << dist[u] + w << endl;

            it = it->next;
        }

    }
    
    return INF;
}


int main(){    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m >> e;
    
    for(int i=0, u, v, c; i<m; i++)
    {
        cin >> u >> v >> c;
        grafo[u].push(par(v, c));
       // grafo[v].push(par(u, c));
    }

    int t, u, v, c;
    while(e--)
    {
        cin >> t;

        if(t&1)
        {
            cin >> u >> v >> c;
            grafo[u].push(par(v, c));
          //  grafo[v].push(par(u, c));
        }
        else
        {
            cin >> u >> v;
            int x = dijkstra(u, v);
            cout << ( x < INF ? x : -1 ) << endl;
        }

    }
    

    return 0;
}