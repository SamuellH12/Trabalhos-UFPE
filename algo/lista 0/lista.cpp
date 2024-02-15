#include <bits/stdc++.h>
#define optimize ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define endl "\n"
#define ll long long
using namespace std;

int main(){
    optimize;

    string ans = "";
    int commas = -1;
    string s;

    while(getline(cin, s))
    {
        int cmm = 0;

        for(int i=0; i<s.size(); i++) 
            if(s[i] == ',')
                cmm++;

        if(cmm > commas)
            commas = cmm, 
            ans = s;           
    }
    
    cout << ans << endl;

    return 0;
}