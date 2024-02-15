#include <iostream>
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


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int t; cin >> t;
    string s;

    for(int cnt=1; cnt<=t; cnt++)
    {
        int tam, n; cin >> tam >> n;
        tam *= 100;

        fila<int> f[2];

        for(int i=0, x; i<n; i++) cin >> x >> s, f[s == "direito"].push(x);

        bool lado = false;
        int ans = 0, tot = 0;

        while(!f[0].empty() || !f[1].empty())
        {
            while(!f[lado].empty() && f[lado].front()+tot <= tam) tot += f[lado].pop();

            lado = !lado;
            ans++;
            tot = 0;
        }

        cout << "Caso " << cnt << ": " << ans << endl;
    }

    return 0;
}