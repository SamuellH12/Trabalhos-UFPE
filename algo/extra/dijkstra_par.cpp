#include <bits/stdc++.h>
#define endl '\n'
#define INF 0x3f3f3f3f3f3f3f3f
#define int long long
using namespace std;
#define clockI  clock_t start, end; start = clock()
#define clockII end=clock(); double time_ = double(end - start) / double(CLOCKS_PER_SEC); cout<<time_<<" s"<<endl

const int MAXN = 5e4;

const int N = 727;      //vertices
const int M = 38'428;   //arestas

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

};



struct par{
    int first, second;
    par(int f, int s) : first(f), second(s) {}
    par(){ first = second = 0; }

    bool operator> (const par a){
        if(first != a.first) return first > a.first;
        return second > a.second;
    }
    bool operator< (const par a) const{
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

lista<par> grafo[N + 10];
int dist[N + 10];

int dijkstra(int source, int sink){

    for(int i=0; i<=N; i++) dist[i] = INF;

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
            // if(op!=3) cout << u << " -> " << v << endl;
            if(dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                pq.push(par(-dist[v], v));
            }
            // else if(op!=3) cout << "dist " << dist[v] << " " << dist[u] + w << endl;

            it = it->next;
        }

    }
    
    return INF;
}

string label[N + 10];

int32_t main(int32_t argc, char* argv[]){    
    int origem = -1, destino = -1, op;
    int id; string s, t, r;

    if(argc > 1) op = 3;

    if(op!=3) cout << "Deseja inserir o codigo numerico do aeroporto (digite 1) ou o codigo de tres letras (digite 2)?" << endl;
    if(op!=3) cout << "(OBS: codigos numericos podem ser acessados no arquivo label.txt) " << endl;
    cin >> op;
    

    if(op&1)
    {
        if(op!=3) cout << "Digite o codigo (numerico) do aeroporto de origem: \n -> ";
        cin >> origem;
        if(op!=3) cout << endl << "Digite o codigo (numerico) do aeroporto de destino: \n -> ";
        cin >> destino;
    }
    else
    {
        if(op!=3) cout << "Digite o codigo (de tres letras) do aeroporto de origem: \n -> ";
        cin >> s;
        if(op!=3) cout << endl << "Digite o codigo (de tres letras) do aeroporto de destino: \n -> ";
        cin >> t;
    }



    freopen("labelPlusGraph.txt", "r", stdin);
    for(int i=0; i<N; i++)
    {
        cin >> id >> r;
        label[id] = r;
    }


    if(origem == -1)
    {
        origem = destino = 0;
        while(label[origem] != s && origem < N) origem++;
        while(label[destino] != t && destino < N) destino++;
    }

    if(origem >= N){cout << "Not Found" << endl; return 0;}
    if(destino >= N){cout << "Not Found" << endl; return 0;}    

    if(op!=3) cout << endl << "de " << label[origem] << "(" << origem << ") para " << label[destino] << "(" << destino << ")" << endl;


    // freopen("grafo_numerico.txt", "r", stdin);
    for(int i=0, u, v, c; i<M; i++)
    {
        cin >> u >> v >> c;
        grafo[u].push(par(v, c));
    }

    clockI;
    auto d = dijkstra(origem, destino);

    if(op!=3) cout << "Distancia: ";
    
    if(d < INF){ if(op!=3) cout << d << endl;}
    else{ if(op!=3) cout << "INF" << endl; }

    clockII;

    return 0;
}

/*
    Quantidade de linhas:   3'606'804   ~ 3.6 * 1e7     (No arquivo original)
    Quantidade de arestas:  38'428      ~ 4 * 1e4       (Únicas, sem repetição de pares de aeroportos)
    Quantidade de vertices: 727         ~ 1e3           (Cada aeroporto diferente representa um vértice)
*/
