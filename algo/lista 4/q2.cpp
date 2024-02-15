#include <bits/stdc++.h>
#define endl '\n'
using namespace std;


template<typename T>    
class fila {

    private:

    struct Node
    {
        T val;
        Node* next = NULL;

        Node(T val) : val(val) {}
    };


    int sz = 0;
    Node* head = NULL;
    Node* tail = NULL;

    public:

    T front(){ return head->val; }
    T back() { return tail->val; }

    T pop()
    {
        Node* old = head;

        head = head->next;

        if(head == NULL) tail = NULL;

        sz--;
        T val = old->val;
        free(old);

        return val;
    }

    void push(T x)
    {
        Node* nw = new Node(x);
        
        if(head == NULL) head = nw;
        if(tail) tail->next = nw;
        
        tail = nw;

        sz++;
    }

    int size(){ return sz; }
    bool empty(){ return !sz; }
};

struct par{
    int first, second;
    par(int f, int s) : first(f), second(s) {}
    par(){ first = second = 0; }
};


const int MAXN = 2e3;
int mat[MAXN][MAXN];
int dist[MAXN][MAXN];


int main(){

    int n, m; cin >> m >> n;

    par bg, ed;

    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
        {
            cin >> mat[i][j];
            if(mat[i][j] == 2) bg = par(i, j);
            if(mat[i][j] == 3) ed = par(i, j);
        }


    fila<par> q;
    q.push(bg);
    dist[bg.first][bg.second] = 1;

    while(!q.empty())
    {
        int i = q.front().first;
        int j = q.front().second;   
        q.pop();

        if( i-1 >= 0 && mat[i-1][j] != 1 && dist[i-1][j] == 0 ) dist[i-1][j] = dist[i][j] + 1, q.push(par(i-1, j));
        if( i+1 <  m && mat[i+1][j] != 1 && dist[i+1][j] == 0 ) dist[i+1][j] = dist[i][j] + 1, q.push(par(i+1, j));
        if( j-1 >= 0 && mat[i][j-1] != 1 && dist[i][j-1] == 0 ) dist[i][j-1] = dist[i][j] + 1, q.push(par(i, j-1));
        if( j+1 <  n && mat[i][j+1] != 1 && dist[i][j+1] == 0 ) dist[i][j+1] = dist[i][j] + 1, q.push(par(i, j+1));
    }

    if(dist[ed.first][ed.second] == 0) cout << "Labirinto Impossivel" << endl;
    else cout << dist[ed.first][ed.second] - 1 << endl;

    return 0;
}