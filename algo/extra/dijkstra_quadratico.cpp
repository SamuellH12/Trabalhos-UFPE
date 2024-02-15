#include <bits/stdc++.h>
#define endl '\n'
#define INF 0x3f3f3f3f3f3f3f3f
#define int long long
using namespace std;

const int MAXN = 5e4;

const int N = 727;      //vertices
const int M = 38'428;   //arestas


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
bool vis[N+10];

int minArray(){
    int u = -1;

    for(int i=0; i<N; i++)
    {
        if(vis[i] || dist[i] >= INF) continue;
        if(u == -1 || dist[i] < dist[u]) u = i;
    }

    return u;
}

int dijkstra(int source, int sink){

    for(int i=0; i<=N; i++) dist[i] = INF, vis[i] = false;

    dist[source] = 0;
    
    while(true)
    {
        int u = minArray();
        // cerr << u << " <-" << endl;
        if(u == -1) break;
        
        vis[u] = true;
        if(u == sink) return dist[u];
        
        auto it = grafo[u].begin();
        while(it != NULL)
        {
            auto v = it->val.first;
            auto w = it->val.second;

            if(dist[v] > dist[u] + w) dist[v] = dist[u] + w;
            // cerr << dist[v] << " ||" << endl; 

            it = it->next;
        }
    }
    
    return INF;
}

string label[N + 10];

int32_t main(){    
    int origem = -1, destino = -1, op;
    int id; string s, t, r;

    cout << "Deseja inserir o codigo numerico do aeroporto (digite 1) ou o codigo de tres letras (digite 2)?" << endl;
    cout << "(OBS: codigos numericos podem ser acessados no arquivo label.txt) " << endl;
    cin >> op;
    

    if(op&1)
    {
        cout << "Digite o codigo (numerico) do aeroporto de origem: \n -> ";
        cin >> origem;
        cout << endl << "Digite o codigo (numerico) do aeroporto de destino: \n -> ";
        cin >> destino;
    }
    else
    {
        cout << "Digite o codigo (de tres letras) do aeroporto de origem: \n -> ";
        cin >> s;
        cout << endl << "Digite o codigo (de tres letras) do aeroporto de destino: \n -> ";
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

    cout << endl << "de " << label[origem] << "(" << origem << ") para " << label[destino] << "(" << destino << ")" << endl;


    // freopen("grafo_numerico.txt", "r", stdin);
    for(int i=0, u, v, c; i<M; i++)
    {
        cin >> u >> v >> c;
        grafo[u].push(par(v, c));
    }

    auto d = dijkstra(origem, destino);

    cout << "Distancia: ";
    
    if(d < INF) cout << d << endl;
    else cout << "INF" << endl;


    return 0;
}

/*
    Quantidade de linhas:   3'606'804   ~ 3.6 * 1e7     (No arquivo original)
    Quantidade de arestas:  38'428      ~ 4 * 1e4       (Únicas, sem repetição de pares de aeroportos)
    Quantidade de vertices: 727         ~ 1e3           (Cada aeroporto diferente representa um vértice)
*/
