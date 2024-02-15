#include <bits/stdc++.h>
const int MAXN = 1e5 + 10;
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





struct Pessoa {
    int id = -1;
    int pq = 0;

    Pessoa(int _id, int _pq){id = _id; pq = _pq; }
    Pessoa(){}

    bool operator> (const Pessoa& a) const
    {
        if(pq != a.pq) return pq > a.pq;
        return id < a.id;
    }
    bool operator< (const Pessoa& a) const
    {
        if(pq != a.pq) return pq < a.pq;
        return id > a.id;
    }

    Pessoa inverso(){ return Pessoa(-id, -pq); }
};

string nomes[MAXN];

int idcnt = 1, vg = 0;
int assento[MAXN];

int main(){
    memset(assento, -1, sizeof assento);
    int f, q;
    int n;
    cin >> f >> q >> n;

    int mx = f * q;

    Heap<Pessoa> sentado, empe;
    Heap<int> cadeira;
    for(int i=0; i<mx; i++) cadeira.push(-i);

    string op, s;
    int x, id;

    while(n--)
    {
        cin >> op >> s >> x;

        while(!empe.empty() && assento[empe.top().id] == -1) empe.pop();
        while(!sentado.empty() && assento[-sentado.top().id] == -1) sentado.pop();

        if(op == "CAD"){
            id = idcnt++;
            nomes[id] = s;

            if(!cadeira.empty())
            {
                int vg = -cadeira.top();
                cadeira.pop();
                
                cout << s << " ("<< id << ") foi alocado(a) na fileira " << vg/q + 1 << endl;

                sentado.push(Pessoa(-id, -x));
                assento[id] = vg;
            }
            else 
            if(Pessoa(-id, -x) < sentado.top())
            {
                Pessoa st = sentado.top();
                empe.push(st.inverso());
                sentado.pop();

                vg = assento[id] = assento[-st.id];
                assento[-st.id] = -2;

                sentado.push(Pessoa(-id, -x));
                // cerr << nomes[-st.id] << " (" << -st.id << ") ficou em pe" << endl;
                cout << s << " ("<< id << ") foi alocado(a) na fileira " << vg/q + 1 << endl;
            }
            else
            {
                empe.push(Pessoa(id, x));
                assento[id] = -2;
                cout << s << " ("<< id << ") nao foi alocado(a) em nenhuma fileira" << endl;
            }
        }
        else
        if(op == "REM")
        {
            int id = x;
            if(assento[id] == -1 || nomes[id] != s) cout << "Inexistente" << endl;
            else 
            {
                cout << "Removido(a)" << endl;

                if(!empe.empty())
                {
                    int vg = assento[id];

                    int id2 = empe.top().id;
                    int peso = empe.top().pq;
                    empe.pop();

                    assento[id2] = vg;
                    sentado.push(Pessoa(-id2, -peso));
                }
                else
                    cadeira.push(-assento[id]);
                
                assento[id] = -1;
                nomes[id] = "NONE";
            }
        }
        else
        if(op == "VER")
        {
            int id = x;
            if(assento[id] == -1 || nomes[id] != s) cout << "Inexistente" << endl;
            else 
            if(assento[id] == -2) cout << "Sem assento" << endl;
            else 
                cout << "Sentado(a) na fileira " << assento[id]/q + 1<< endl;
        }
    }


    return 0;
}

