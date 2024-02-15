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

struct aresta {
    int u, v, w;
    aresta(int u, int v, int w) : u(u), v(v), w(w) {}
    aresta(){}
};

struct Node
{
    aresta val;
    Node* next = NULL;

    Node(aresta val) : val(val) {}
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


lista<aresta> arestas;
int dist[N + 10];

int bellman(int source, int sink){

    for(int i=0; i<=N; i++) dist[i] = INF;
	dist[source] = 0;

	for (int i = 0; i <= N; i++)
    {
		auto it = arestas.begin();
        while(it != NULL)
        {
            auto u = it->val.u;
            auto v = it->val.v;
            auto w = it->val.w;

            if(dist[v] > dist[u] + w) dist[v] = dist[u] + w;

            it = it->next;
        }
    }

    return dist[sink];
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
        arestas.push(aresta(u, v, c));
    }

    clockI;
    auto d = bellman(origem, destino);

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
