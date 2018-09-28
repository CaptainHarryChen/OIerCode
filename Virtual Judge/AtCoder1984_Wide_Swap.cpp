#include<cstdio>
#include<set>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=500005;

int N,K,A[MAXN];
int pos[MAXN];
vector<int> adj[MAXN];
set<int> L,R;
priority_queue<int,vector<int>,greater<int> > Q;
vector<int> stk;
int pri[MAXN];
int deg[MAXN];

int main()
{
    scanf("%d%d",&N,&K);
    for(int i=1;i<=N;i++)
        scanf("%d",&A[i]),pos[A[i]]=i;
    for(int i=1;i<=K;i++)
        R.insert(A[i]);
    set<int>::iterator x,y;
    for(int i=1;i<=N;i++)
    {
        x=L.upper_bound(A[i]);
        y=R.upper_bound(A[i]);
        if(x!=L.end())
        {
            adj[i].push_back(pos[*x]);
            deg[pos[*x]]++;
        }
        if(y!=R.end())
        {
            adj[i].push_back(pos[*y]);
            deg[pos[*y]]++;
        }
        L.insert(A[i]);
        if(i-K+1>0)
            L.erase(A[i-K+1]);
        if(i+K<=N)
            R.insert(A[i+K]);
        R.erase(A[i]);
    }

    for(int i=1;i<=N;i++)
        if(deg[i]==0)
            Q.push(i);
    while(!Q.empty())
    {
        int u=Q.top();
        Q.pop();
        stk.push_back(u);
        for(int i=0;i<(int)adj[u].size();i++)
        {
            deg[adj[u][i]]--;
            if(deg[adj[u][i]]==0)
                Q.push(adj[u][i]);
        }
    }
    for(int i=0;i<N;i++)
        pri[stk[i]]=i+1;
    for(int i=1;i<=N;i++)
        printf("%d\n",pri[i]);

    return 0;
}

