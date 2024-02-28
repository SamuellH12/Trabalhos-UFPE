#include <bits/stdc++.h>
#define optimize ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define ALL(x) x.begin(), x.end()
#define endl "\n"
#define ll long long
#define vi vector<int>
#define pii pair<int,int>
#define INF 0x3f3f3f3f
const int MAXN = 1e6 + 5;
using namespace std;



int main(){

	int n; 
	cin >> n;

	vi arr(n), aux(n);

	for(auto &x : arr) cin >> x;


	for(int p=2; p <= 2*n; p *= 2)
	{
		for(int l=0, r, m, i, j, k; l < n; l += p)
		{
			r = min(l+p-1, n-1);
			m = l + (p/2) - 1;

			for(i=l; i<=r; i++) aux[i] = arr[i];

			i = k = l;
			j = m+1;

			while(i <= m && j <= r) arr[k++] = (aux[i] < aux[j] ? aux[i++] : aux[j++]);
			while(i <= m) arr[k++] = aux[i++];
			while(j <= r) arr[k++] = aux[j++];
		}
	}


	for(auto &x : arr) cout << x << ' '; cout << endl;


	return 0;	
}
