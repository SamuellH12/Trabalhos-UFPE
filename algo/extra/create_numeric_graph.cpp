#include <bits/stdc++.h>
using namespace std;

// AVL para realizar compressão de coordenadas
template<typename T, typename S>    
class AVL_MAP {

    private:
    struct Node
    {
        T key;
        S val;
        Node* L = NULL;
        Node* R = NULL;
        int h = 1; 

        Node(T key, S val) : key(key), val(val) {}

        int FB(){ return (R ? R->calcH() : 0) - (L ? L->calcH() : 0);  }
        int calcH(){ return h = 1 + max((R ? R->h : 0), (L ? L->h : 0)); }
    };

    int sz = 0;
    Node* root = NULL;

    Node* rotacaoDir(Node* u){
        Node* v = u->L;
        u->L = v->R;
        v->R = u;
        
        u->calcH();
        v->calcH();
        
        return v;
    }

    Node* rotacaoEsq(Node* u){
        Node* v = u->R;
        u->R = v->L;
        v->L = u;
        
        u->calcH();
        v->calcH();
        
        return v;
    }

    Node* rebalancear(Node *u){
        u->calcH();

        if(u->FB() <= -2 && u->L->FB() <=  0 ) u = rotacaoDir(u);
        if(u->FB() <= -2 && u->L->FB() >=  1 ) u->L = rotacaoEsq(u->L), u = rotacaoDir(u);
        
        if(u->FB() >=  2 && u->R->FB() >=  0 ) u = rotacaoEsq(u);
        if(u->FB() >=  2 && u->R->FB() <= -1 ) u->R = rotacaoDir(u->R), u = rotacaoEsq(u);

        return u;
    }

    Node* insert(Node* u, T key, S val){
        if(!u){ sz++; return new Node(key, val); }
        if(key == u->key) return u;
        if(key < u->key) u->L = insert(u->L, key, val);
        if(key > u->key) u->R = insert(u->R, key, val);
        
        return u = rebalancear(u);
    }

    Node* remove(Node* u, T key){
        if(!u) return NULL;
        if(u->key == key)
        {
            if(!u->L && !u->R){ delete u; return NULL; }        //folha
            if(!u->L){ return u->R = rebalancear(u->R); }       //1 filho R
            if(!u->R){ return u->L = rebalancear(u->L); }       //1 filho L
                                                                //2 filhos
            Node* s = u->R;
            while(s->L) s = s->L;

            u->key = s->key;
            u->R = remove(u->R, s->key);

            return u = rebalancear(u);
        }
        if(key < u->key) u->L = remove(u->L, key);
        if(key > u->key) u->R = remove(u->R, key);
        return u = rebalancear(u);
    }

    public:

    void insert(T key, S val){ root = insert(root, key, val); }

    bool remove(T key){
        if(nivel(key)==-1) return false;
        sz--;
        root = remove(root, key);
        return true;
    }

    bool count(T key){ return ~nivel(key); }

    int nivel(T key){
        int nvl = 0;
        Node* x = root;

        while( x && x->key != key) x = (key < x->key ? x->L : x = x->R), nvl++;

        return( x ? nvl : -1);
    }

    int size(){return sz;}

    S& operator[](T key) {
        if(nivel(key) == -1) insert(key, S());

        Node* x = root;
        while( x && x->key != key) x = (key < x->key ? x->L : x = x->R); 

        return x->val;
    }
};




int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);
    
    freopen("grafo.txt", "r", stdin);
    freopen("grafo_numerico.txt", "w", stdout);

    AVL_MAP<string, int> mapa;

    string U, V; 
    int u, v, d;

    while(cin >> U >> V >> d)
    {
        if(!mapa.count(U)) mapa[U] = mapa.size();
        if(!mapa.count(V)) mapa[V] = mapa.size();
        
        u = mapa[U];
        v = mapa[V];

        cout << u << " " << v << " " << d << endl;
    }

    return 0;
}


/*
    Quantidade de linhas:   3'606'804   ~ 3.6 * 1e7     (No arquivo original)
    Quantidade de arestas:  38'428      ~ 4 * 1e4       (Únicas, sem repetição de pares de aeroportos)
    Quantidade de vertices: 727         ~ 1e3           (Cada aeroporto diferente representa um vértice)
*/