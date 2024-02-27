#include <bits/stdc++.h>
#define optimize ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define endl "\n"
using namespace std;

template<typename T> struct vetor {
    private:
    T* data;
    int sz=0, lg=0;
    void _resize(){
        lg++;
        T* temp = data;
        data = new T[1<<lg];
        for(int i=0; i<sz; i++) data[i] = temp[i];
    }

    public:
    vetor(){ data = new T[2]; lg = 1, sz = 0;}

    vetor(int n) : sz(n){
        while((1<<lg) <= n) lg++;
        data = new T[1<<lg];
    }

    vetor(int n, T fill) : sz(n){
        while((1<<lg) <= n) lg++;
        data = new T[1<<lg];
        for(int i=0; i<sz; i++) data[i] = fill;
    }

    void push_back(T x){ data[sz++] = x; if(sz == (1<<lg)) _resize(); }
    void pop_back(){ if(sz) sz--; }
    int size(){ return sz; }
    T& operator[](int i){ assert(i < sz); return data[i]; }
    T* begin(){return data; }
    T* end() {return data + sz;}
};


int main(){

    vetor<int> sla (10);

    while(true)
    {
        int op; cin >> op;

        if(op == 0){ int x; cin >> x; sla.push_back(x); }

        if(op == 1) sla.pop_back();

        if(op == 2)
        {
            for(int i=0; i<sla.size(); i++) cout << sla[i] << " "; cout << endl;
            for(auto x : sla) cout << x << " "; cout << endl;
        }

        if(op == 3)
        {
            int i,x; 
            cin >> i >> x;
            sla[i] = x;
        }
        
        if(op == 4) cout << "sz " << sla.size() << endl;

        if(op == 5)
        {
            int v; cin >> v;
            for(auto &x : sla) x = v;
        }

        cout << endl;
    }

    return 0;
}