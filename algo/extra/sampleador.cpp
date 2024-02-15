#include <bits/stdc++.h>
using namespace std;


int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);
    freopen("Airports2.csv", "r", stdin);
    freopen("sample.txt", "w", stdout);

    string s; int cnt = 0;
    while( getline(cin, s) && cnt++ < 1000)
    {
        cout << s << endl;
    }

    cout << cnt << endl;

    return 0;
}