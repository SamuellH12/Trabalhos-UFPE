#include <bits/stdc++.h>
const int MAXN = 1e4;
using namespace std;


template<typename T>    
class Heap {

    T heap[MAXN];
    int sz = 0;

    private:
    void max_heapfy(int i){
        if(i > sz/2) return;

        int l = i*2, r = i*2+1, mx;

        if(r > sz) mx = l;
        else mx = (heap[l] > heap[r] ? l : r);

        if(heap[mx] > heap[i])
        {
            swap(heap[mx], heap[i]);
            max_heapfy(mx);
        }
    }

    void heapfy_reverse(int i)
    {
        if(!i) return;
        int l = i*2, r = i*2+1, mx = i;
         
        if(l<=sz && r <= sz) mx = (heap[l] > heap[r] ? l : r);
        else mx = (l <= sz ? l : i);

        if(heap[mx] > heap[i]) swap(heap[mx], heap[i]);

        heapfy_reverse(i>>1);
    }

    public:
    
    void push(T x)
    {
        sz++;
        heap[sz] = x;
        heapfy_reverse(sz);
    }

    T pop()
    { 
        swap(heap[1], heap[sz]);
        sz--;
        max_heapfy(1);
        return heap[sz+1];
    }

    T top(){ return heap[1]; }

    int size(){ return sz; }

    bool empty(){ return !sz; }

    void print(){
        for(int i=1; i<=sz; i++) cerr << heap[i].id << " " << heap[i].pq << " | ";
        cerr << endl;
    }

};



int main(){

    Heap<int> pq;
    string op;
    int x;

    while(true){
        cin >> op;

        if(op == "print") pq.print();
        if(op == "top") cout << "top " << pq.top() << endl;
        if(op == "pop") cout << "pop " << pq.pop() << endl;
        if(op == "push"){ cin >> x; pq.insert(x); }
    }


    return 0;
}