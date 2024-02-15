#include <bits/stdc++.h>
#define endl "\n"
using namespace std;

template<typename T>    
class AVL {

    private:
    struct Node
    {
        T val;
        Node* L = NULL;
        Node* R = NULL;
        int h = 1; 

        Node(T val) : val(val){}

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

    Node* insert(Node* u, T val){
        if(!u) return new Node(val);
        if(val == u->val) return u;
        if(val < u->val) u->L = insert(u->L, val);
        if(val > u->val) u->R = insert(u->R, val);
        
        return u = rebalancear(u);
    }

    Node* remove(Node* u, T val){
        if(!u) return NULL;
        if(u->val == val)
        {
            if(!u->L && !u->R){ delete u; return NULL; }        //folha
            if(!u->L){ return u->R = rebalancear(u->R); }       //1 filho R
            if(!u->R){ return u->L = rebalancear(u->L); }       //1 filho L
                                                                //2 filhos
            Node* s = u->R;
            while(s->L) s = s->L;

            u->val = s->val;
            u->R = remove(u->R, s->val);

            return u = rebalancear(u);
        }
        if(val < u->val) u->L = remove(u->L, val);
        if(val > u->val) u->R = remove(u->R, val);
        return u = rebalancear(u);
    }

    public:

    void insert(T val){ root = insert(root, val); }

    bool remove(T val){
        if(nivel(val)==-1) return false;
        root = remove(root, val);
        return true;
    }

    int nivel(T val){
        int nvl = 0;
        Node* x = root;

        while( x && x->val != val) x = (val < x->val ? x->L : x = x->R), nvl++;

        return( x ? nvl : -1);
    }

    void listarArestas(Node* u = NULL)
    {
        if(!u) u = root;
        if(u->L) cout << u->val << " " << u->L->val << endl, listarArestas(u->L);
        if(u->R) cout << u->val << " " << u->R->val << endl, listarArestas(u->R);
    }

    void printEm(Node* u = NULL, bool comma = false){
        if(!u) u = root;
        if(u == root) cout << "[";

        if(u && u->L) printEm(u->L, comma), comma = true;
        if(u) cout << (comma ? "," : "" ) << u->val;
        if(u && u->R) printEm(u->R, true);

       if(u == root) cout << "]\n";
    }

    void printPre(Node* u = NULL){
        if(!u) u = root;
        if(u == root) cout << "[";

        if(u) cout << (u == root ? "" : "," ) << u->val;
        if(u && u->L) printPre(u->L);
        if(u && u->R) printPre(u->R);

        if(u == root) cout << "]\n";
    }

    void printPos(Node* u = NULL){
        if(!u) u = root;
        if(u == root) cout << "[";

        if(u && u->L) printPos(u->L);
        if(u && u->R) printPos(u->R);

        if(u) cout << u->val << (u == root ? "" : "," );    

        if(u == root) cout << "]\n";
    }
};

const int MOD = 100;

int32_t main(){ 
    ios::sync_with_stdio(false); cin.tie(NULL), cout.tie(NULL);
    AVL<int> avl;

    string op, od;
    int x; 
    int cnt = 0;

    while(cin >> op && op != "FIM")
    {
        if(op == "ADICIONA") cin >> x, avl.insert(x);
        
        if(op == "REMOVE")
        {
            cin >> x;
            if(!avl.remove(x)) cout << "Valor " << x << " inexistente" << endl;
        }
        
        if(op == "NIVEL")
        {
            cin >> x;
            int nvl = avl.nivel(x);

            if(~nvl) cout << "Nivel de " << x << ": " << nvl << endl;
            else cout << "Valor " << x << " inexistente" << endl;
        }
        
        if(op == "PRINT")
        {
            cin >> od;
            if(od == "PREORDEM") avl.printPre();
            if(od == "EMORDEM")  avl.printEm();
            if(od == "POSORDEM") avl.printPos();
        }

        if(op == "LISTAR"){ cout << endl; avl.listarArestas(); cout << endl; }
    }


    return 0;
}