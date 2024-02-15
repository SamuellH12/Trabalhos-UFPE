#include <bits/stdc++.h>
const int MAXN = 1e4;
const int MOD = 1000003;
#define INF 0x3f3f3f3f
using namespace std;


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
    
    void insert(T x)
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

    void print(){
        for(int i=1; i<=sz; i++) cerr << heap[i].id << " " << heap[i].pq << " | ";
        cerr << endl;
    }

};


struct Pessoa {
    int id = -1;
    int pq = 0;

    Pessoa(int _id, int _pq){id = _id; pq = _pq; }
    Pessoa(){}

    bool operator> (const Pessoa& a)
    {
        if(pq != a.pq) return pq > a.pq;
        return id < a.id;
    }
};

string nomes[MAXN];
int assentos[MAXN];
int pessoa[MAXN];
int idcnt = 1, vg = 0;


int main(){
    memset(pessoa, -1, sizeof pessoa);
    memset(assentos, -1, sizeof assentos);
    Pessoa sla(10, 2);
    cerr << sla.id << " " << sla.pq << endl;
    
    int f, q;
    int n;
    cin >> f >> q >> n;

    int mx = f * q;

    cerr << "o";
    Heap<Pessoa> sentado, empe;
    cerr << "k\n";

    sentado.insert(sla);
    if(sentado.size()) cerr << "topo de sent " << sentado.top().id << " " << sentado.top().pq << endl;


    string op, s;
    int x, id;

    while(n--)
    {
        // verificar se o topo de alguma fila foi removido
        while(sentado.size() && nomes[sentado.top().id] == "") sentado.pop();
        while(empe.size() && nomes[empe.top().id] == "") empe.pop();


        cin >> op >> s >> x;

        if(op == "CAD")
        {
            id = idcnt++;
            nomes[id] = s;
            Pessoa at(id, -x);
            if(vg < mx)
            {
                assentos[vg] = id;
                pessoa[id] = vg;

                sentado.insert(at);
                cerr << s << " id" << id << " pq" << x << endl;
                
                cout << s << " ("<< id << ") foi alocado(a) na fileira " << vg/q + 1 << endl;
                
                vg++;
            }
            else
            if( sentado.top() > at ) //lembrando que a priridade tá negativa
            {
                auto [su, pi] = sentado.pop();
                Pessoa old(su, -pi);
                empe.insert(old);

                int as = pessoa[su];

                assentos[as] = id;
                pessoa[id] = as;

                pessoa[su] = -1;

                sentado.insert(at);

                cout << s << " ("<< id << ") foi alocado(a) na fileira " << as/q + 1 << endl;
            }
            else 
            {
                at.pq *= -1;
                at.id *= -1;
                empe.insert(at);
                cout << s << " ("<< id << ") nao foi alocado(a) em nenhuma fileira" << endl;
            }

        }
        else
        if(op == "REM")
        {

            if(nomes[x] != s) cout << "Inexistente" << endl;
            else
            {
                nomes[x] = "";
                cout << "Removido(a)" << endl;

                if(pessoa[x] != -1)
                {
                    if(empe.size()){
                        auto [nw, pq] = empe.pop();
                        nw *= -1;
                        pessoa[nw] = pessoa[x];
                        assentos[pessoa[x]] = nw;
                    }
                    else assentos[pessoa[x]] = -1;
                }

                pessoa[x] = -1;
            }
        }
        else
        if(op == "VER")
        {
            if(nomes[x] != s) cout << "Inexistente" << endl;
            else
            if(pessoa[x] == -1) cout << "Sem assento" << endl;
            else cout << "Sentado(a) na fileira " << pessoa[x]/q +1 << endl;
        }

        cerr << "sentados " << sentado.size() << " || em pe " << empe.size() << endl;
        if(sentado.size()) cerr << "topo de sent " << sentado.top().id << " " << sentado.top().pq << endl;
        if(empe.size()) cerr << "topo de emp " << empe.top().id << " " << empe.top().pq << endl;
        sentado.print();
    }




    return 0;
}