#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int MAXN = 1e4 + 10;

int pai[MAXN], sz[MAXN];

int find(int u){ return u == pai[u] ? u : pai[u] = find(pai[u]); }

void join(int u, int v){
    u = find(u);
    v = find(v);

    if(u == v) return;
    if(sz[v] > sz[u]) swap(v, u);

    pai[v] = u;
    sz[u] += sz[v];
}

struct par{ int u, v; par(int u, int v) : u(u), v(v){} };

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t, caso=0; cin >> t; 
    while(t--)
    {
        int n, m, q;
        cin >> n >> m >> q;

        for(int i=0; i<=n*n; i++) sz[i] = 1, pai[i] = i;

        int maxM = 2*(n*n-n), p = 2*n-1;

        auto aresta = [&](int id)
        {
            int nvl = id/p;

            //parede lateral
            if(id%p < n-1) return par((nvl*n) + id%p , (nvl*n) + id%p + 1);

            return par((nvl*n) + id%p - (n-1) , (nvl*n) + id%p - (n-1) + n);
        };

        for(int i=0, id; i<m; i++)
        {
            cin >> id;
            auto [u, v] = aresta(id);
            join(u, v);
        }

        int u, v, qa=0;
        while(q--)
        {
            cin >> u >> v;
            cout << caso << "." << qa++ << " " << (find(u) == find(v)) << endl;
        }
        
        caso++;
        cout << endl;
    }

    return 0;
}