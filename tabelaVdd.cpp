#include <bits/stdc++.h>
#define pii pair<int, int>
#define vii vector<pii>
#define vi vector<int>
using namespace std;

const int MAXN = 1e4;

vi grafo[MAXN];
int tipo[MAXN];
int value[30];
string eq; 
int n, idx;
// [A, B, C, ...] -> [1, 2, 3, ...] 
// + -> -2 
// e -> -3 
// ! -> -1 

char sla[] = {' ', '!', '+', 'e'};

bool solve(int u)
{
    if(tipo[u] >= 0) return value[u];

    if(tipo[u] == -1) return !solve(grafo[u][0]);
    if(tipo[u] == -2) return solve(grafo[u][0]) || solve(grafo[u][1]);
    if(tipo[u] == -3) return solve(grafo[u][0]) && solve(grafo[u][1]);

    return 0;
}

int create(int l, int r)
{
    stack<int> st, op;

    for(int i=l; i<=r; i++)
    {
        if(eq[i] <= 'Z' && eq[i] >= 'A') st.push(eq[i]-'A');

        if(eq[i] == '(')
        {
            int ide;    
            int nr = i, cnt = 1;
            while(cnt > 0)
            {
                nr++;
                if(eq[nr] == '(') cnt++;
                if(eq[nr] == ')') cnt--;
            }

            ide = create(i+1, nr-1);
            i = nr;

            st.push(ide);
        }


        while(!op.empty() && (op.top() == 1 || st.size() >= 2))
        {
            int p = op.top();
            op.pop();
            
            int id = idx++;
            tipo[id] = -p;
            
            if(p == 1)
            {
                grafo[id].push_back(st.top());
                st.pop();
            }
            else 
            {
                grafo[id].push_back(st.top()); 
                st.pop();
                grafo[id].push_back(st.top());
                st.pop();
            }

            st.push(id);
        }
        

        if(eq[i] == '!') op.push(1); // = 1;
        if(eq[i] == '+') op.push(2); // = 2;
        if(eq[i] == 'e') op.push(3); // = 3;
    }

    return st.top();
}


int main(){


    cout << "(A+B)  ->  A OU B" << endl;
    cout << "(AeB)  ->  A  E B" << endl;
    cout << "!A   ->  NAO A " << endl;
    cout << "CUIDADO: operacoes SEM parenteses podem apresentar comportamente INESPERADO." << endl;
    cout << endl << endl;
   
    cout << "Numero de variaveis -> ";
    
    cin >> n;
    idx = n;

    cout << "O nome das variaveis devem ser: ";
    
    for(int i=0; i<n; i++) cout << char('A'+i) << " ";
    cout << endl << endl;


    cout << "Insira a equacao: " << endl << endl;
    cout << "-> ";
    getline(cin, eq);
    getline(cin, eq);

    int root = create(0, eq.size()-1);

    for(int i=0; i<n; i++) cout << "+-"; cout << "+---+" << endl;
    for(int i=0; i<n; i++) cout << "|" << char('A'+i); cout << "|Ans|" << endl;
    
    for(int m=0; m<(1<<n); m++)
    {
        memset(value, -1, sizeof value);

        for(int i=0; i<n; i++) 
            cout << "|" << bool(value[i] = m&(1<<(n-1-i))); 
        
        cout << "| " << solve(root) <<  " |" << endl;
    }

    for(int i=0; i<n; i++) cout << "+-"; cout << "+---+" << endl;


    return 0;
}


/*
VERSAO COM PARENTESES OBRIGATORIO PARA NEGACAO

int create(int l, int r){
    // cerr << l << " lr " << r << endl;
    stack<int> st;
    int op = 0;

    for(int i=l; i<=r; i++)
    {
    //    cerr << eq[i] << " " << op << endl;

        if(eq[i] <= 'Z' && eq[i] >= 'A')
        {
            if(!op) st.push(eq[i]-'A');
            else
            {
                int id = idx++;
                tipo[id] = -op;
                
                if(op == 1) grafo[id].push_back(eq[i]-'A');
                else 
                {
                    grafo[id].push_back(st.top());
                    grafo[id].push_back(eq[i]-'A');
                    st.pop();
                }

                //cerr << " -> " << id << sla[op] << endl;

                st.push(id);
                op = 0;
            }
            continue;
        }

        if(eq[i] == '(')
        {
            int ide;    
            int nr = i, cnt = 1;
            while(cnt > 0)
            {
                nr++;
                if(eq[nr] == '(') cnt++;
                if(eq[nr] == ')') cnt--;
            }

            ide = create(i+1, nr-1);
            i = nr;

            if(!op) st.push(ide);
            else
            {
                int id = idx++;
                tipo[id] = -op;
                
                if(op == 1) grafo[id].push_back(ide);
                else 
                {
                    grafo[id].push_back(st.top());
                    grafo[id].push_back(ide);
                    st.pop();
                }


                st.push(id);
                op = 0;
            }
            continue;
        }


        if(eq[i] == '!') op = 1;
        if(eq[i] == '+') op = 2;
        if(eq[i] == 'e') op = 3;

    }

    return st.top();
}

*/