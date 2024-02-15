#include <bits/stdc++.h>
using namespace std;

class HashMap {

    class Lista {

        private:

        struct Node
        {
            string val = "sla";
            Node* next = NULL;

            Node(string val) : val(val) { }
        };


        int sz = 0;
        Node* head = NULL;    

        public:

        int find(string& x)
        {
            Node* at = head;
            int i=0;

            while(at)
            {
                if(at->val == x) return i;
                at = at->next;
                i++;
            }

            return -1;
        }

        bool remove(string& x)
        {
            Node* at = head;
            Node* lst = NULL;
           // cerr << "removing " << x << endl;

            while(at != NULL)
            {
                // cerr << "is " << at->val << "??? " << at->next << endl;
                if(at->val == x)
                {
                    if(at == head) head = at->next;
                    else lst->next = at->next;
                    sz--;
                    return true;
                }
                
                lst = at;
                at = at->next;
                if(!at) break;
            }

            return false;
        }

        void push(string x)
        {
            Node* nw = new Node(x);
            
            nw->next = head;
            head = nw;
            
            sz++;
        }

        int size(){ return sz; }

        bool empty(){ return !sz; }
    };

    private:

    Lista* mp; //[1000];
    int MOD;

    public:

    int hashFunc(string& s){

        int hsh = 0;

        for(int i=1; i<=s.size(); i++)
            hsh = (hsh + ( s[i-1] * i ) * 17 ) % MOD;
        
        //cerr << s << " " << hsh << endl;
        return hsh;
    }

    HashMap(int mod)
    {
        // mp = (Lista*) malloc(mod * sizeof(Lista));
        mp = new Lista[mod];
        MOD = mod;
       // cerr << "succes\n";
    }

    void insert(string& s)
    {
        int hsh = hashFunc(s);
       // cerr << " insert  " << s << " at " << hsh << endl;
        mp[hsh].push(s);
    }

    int find(string &s)
    {
        int hsh = hashFunc(s);
        return mp[hsh].find(s);
    }

    bool remove(string &s)
    {
        int hsh = hashFunc(s);
        return mp[hsh].remove(s);
    }

};


int main(){

    int m, c; cin >> m >> c;

    HashMap mp(m);

    string op, s;

    while(c--)
    {
        cin >> op >> s;
        mp.insert(s);
    }

    int n; cin >> n;

    while(n--)
    {
        cin >> op >> s;

        if(op == "POST") mp.insert(s);
        else
        if(op == "DELETE")
        {
            if(mp.remove(s)) cout << "DELETADO" << endl;
        }
        else
        if(op == "GET")
        {
            int j = mp.find(s); 
            if(~j) cout << mp.hashFunc(s) << " " << j+1 << endl;
            else cout << "404 - NOT FOUND" << endl;
        }


    }


    return 0;
}