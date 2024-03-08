#include <bits/stdc++.h>
using namespace std;
#define INF 1e8

int main(){
    int n, w;
    cin >> n >> w;
    
    int peso[n+1];
    int valor[n+1];
    int dp[n+1][w+1];

    for(int i=1; i<=n; i++) 
        cin >> valor[i] >> peso[i];
    
    for(int k=0; k<=w; k++) dp[0][k] = 0;

    for(int i=1; i<=n; i++)
        for(int k=0; k<=w; k++)
            if(peso[i] <= k)
                dp[i][k] = max(dp[i-1][k], dp[i-1][k-peso[i]] + valor[i]);
            else
                dp[i][k] = dp[i-1][k];


    cout << dp[n][w] << endl;

    return 0;
}



//
// int solve(int i, int k){
//     if(i == n+1) return 0;
//     if(dp[i][k] != -1) return dp[i][k];

//     int pegar = -INF;
//     if(peso[i] <= k) pegar = solve(i+1, k-peso[i]) + valor[i];

//     int nao = solve(i+1, k);
    
//     return dp[i][k] = max(pegar, nao);
// }

// void recuperar(int i, int k){
//     if(i == n+1) return;

//     if( peso[i] <= k && solve(i, k) == solve(i+1, k-peso[i]) + valor[i])
//     {
//         cout << valor[i] << " " << peso[i] << endl;
//         recuperar(i+1, k-peso[i]);
//     }
//     else
//         recuperar(i+1, k);
// }

    // memset(dp, -1, sizeof dp);
    // cout << solve(1, w) << endl;
    // cout << "Itens pegos: " << endl;
    // recuperar(1, w);