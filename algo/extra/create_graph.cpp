#include <bits/stdc++.h>
using namespace std;


// Para ler os elementos separando-os por vírgulas
bool read(string &s){ 
    s = "";
    char c; 
    
    while(true)
    {
        c = getchar();
        if(c == ',' || c == '\n' || (int)(c) == -1) break;
        if(c != '"') s += c; 
    }

    return !s.empty();
}


// AVL para evitar elementos repetidos e otimizar a quantidade de arestas necessarias
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
        if(!u){ sz++; return new Node(val); }
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
        sz--;
        root = remove(root, val);
        return true;
    }

    bool count(T val){ return ~nivel(val); }

    int nivel(T val){
        int nvl = 0;
        Node* x = root;

        while( x && x->val != val) x = (val < x->val ? x->L : x = x->R), nvl++;

        return( x ? nvl : -1);
    }

    int size(){return sz;}
};


string 
Origin_airport, 
Destination_airport,
Origin_city, Origin_state,
Destination_city, Destination_state,
Passengers,
Seats,
Flights,
Distance,
Fly_date,
Origin_population,
Destination_population,
Org_airport_lat,
Org_airport_long,
Dest_airport_lat,
Dest_airport_long;


int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);
    
    freopen("Airports2.csv", "r", stdin);
    freopen("grafo.txt", "w", stdout);


    ////// ler o cabeçalho //////
    read(Origin_airport);
    read(Destination_airport);
    read(Origin_city);      // read(Origin_state);          // -
    read(Destination_city); // read(Destination_state);     // -
    read(Passengers);
    read(Seats);
    read(Flights);
    read(Distance);
    read(Fly_date);
    read(Origin_population);
    read(Destination_population); 
    read(Org_airport_lat);
    read(Org_airport_long);
    read(Dest_airport_lat);
    read(Dest_airport_long );
    ///////////////////////////


    auto canRead = [&](){
        return  read(Origin_airport)&&  
        read(Destination_airport)   &&  
        read(Origin_city)           &&  
        read(Origin_state)          &&  // + 
        read(Destination_city)      &&  
        read(Destination_state)     &&  // + 
        read(Passengers)            &&  
        read(Seats)                 &&  
        read(Flights)               &&  
        read(Distance)              &&  
        read(Fly_date)              &&  
        read(Origin_population)     &&  
        read(Destination_population)&&  
        read(Org_airport_lat)       &&  
        read(Org_airport_long)      &&  
        read(Dest_airport_lat)      &&  
        read(Dest_airport_long );
    };


    AVL<string> mapa, airports;
    string s, id;
    int cnt = 0;

    while( canRead() )
    {
        id = Origin_airport + Destination_airport + Distance;

        if(mapa.count(id)) continue;    //para evitar arestas repetidas
        mapa.insert(id);

        airports.insert(Origin_airport);
        airports.insert(Destination_airport);

        cout << Origin_airport <<  " " << Destination_airport << " " << Distance << endl;
    }

    cerr << "Quantidade de arestas:  " << mapa.size() << endl;
    cerr << "Quantidade de vertices: " << airports.size() << endl;

    return 0;
}


/*
    Quantidade de linhas:   3'606'804   ~ 3.6 * 1e7     (No arquivo original)
    Quantidade de arestas:  38'428      ~ 4 * 1e4       (Únicas, sem repetição de pares de aeroportos)
    Quantidade de vertices: 727         ~ 1e3           (Cada aeroporto diferente representa um vértice)
*/