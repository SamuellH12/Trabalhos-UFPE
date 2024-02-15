#include <bits/stdc++.h>
using namespace std;

class HashMap {

    class Lista {

        private:

        struct Node
        {
            string val;
            Node* next = NULL;

            Node(string val) : val(val) {}
        };


        int sz = 0;
        Node* head = NULL;    

        public:

        bool find(string& x)
        {
            Node* at = head;

            while(at)
            {
                if(at->val == x) return true;
                at = at->next;
            }

            return false;
        }

        bool remove(string& x)
        {
            Node* at = head;
            Node* lst = NULL;

            while(at)
            {
                if(at->val == x)
                {
                    if(lst) head = at->next;
                    else lst->next = at->next;
                    return true;
                }
                
                lst = at;
                at = at->next;
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

    Lista* mp = NULL;
    int mod;

    int hashFunc(string& s){

        int hsh = 0;

        for(int i=1; i<=s.size(); i++)
            hsh = (hsh + ( s[i-1] * i ) * 17 ) % mod;
        
        cerr << s << " " << hsh << endl;
        return hsh;
    }


    public:

    HashMap(int mod)
    {
        while(!mp) mp = (Lista*) malloc(mod * sizeof(Lista));
        cerr << "succes\n";
    }

    void post(string& s)
    {
        int hsh = hashFunc(s);
        mp[hsh].push(s);
    }

    bool get(string &s)
    {
        int hsh = hashFunc(s);
        return mp[hsh].find(s);
    }

    void remove(string &s)
    {
        int hsh = hashFunc(s);
        mp[hsh].remove(s);
    }

};