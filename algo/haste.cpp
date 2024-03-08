#include <bits/stdc++.h>
using namespace std;
#define INF 1e8
const int MAXN = 500;

int dp[MAXN][MAXN];

int solve(int corte, int barra, vector<int> &valor){
    if(barra == 0) return 0;
    if(dp[corte][barra] != -1) return dp[corte][barra];

    int ct = 0, nao = 0;

    //cortar nova barra
    if(corte <= barra)
        ct = solve(1, barra-corte, valor) + valor[corte];

    //continuar barra
    if(corte < barra)
        nao = solve(corte+1, barra, valor);

    return dp[corte][barra] = max(ct, nao);
}


int main(){
    memset(dp, -1, sizeof dp);
    int n; cin >> n;

    vector<int> valor(n+1, 0);
    for(int i=1; i<=n; i++) cin >> valor[i];

    cout << solve(n, n, valor) << endl;


    vector<int> pd(n+1, 0);

    for(int tam=1; tam<=n; tam++)
        for(int corte=1; corte<=tam; corte++)
            pd[tam] = max(pd[tam], pd[tam-corte] + valor[corte]);
    


    cout << pd[n] << endl;


    return 0;
}



