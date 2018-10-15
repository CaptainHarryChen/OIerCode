#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<set>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int N;
set<int> E[MAXN];
map<int,int> cnt[MAXN];
queue<pair<int,int>> Q;

int fa[MAXN];
int Root(int x)
{return fa[x]==0?x:(fa[x]=Root(fa[x]));}

void Link(int u,int v)
{
    E[u].insert(v);
    E[v].insert(u);
    if(u>v)
        swap(u,v);
    cnt[u][v]++;
    if(cnt[u][v]>2)
    {
        puts("NO");
        exit(0);
    }
    if(cnt[u][v]==2)
        Q.emplace(u,v);
}
void Cut(int u,int v)
{
    E[u].erase(v);
    if(u>v)
        swap(u,v);
    cnt[u].erase(v);
}

int main()
{
    scanf("%d",&N);
    for(int i=1;i<=2*N-2;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        Link(u,v);
    }
    for(int i=1;i<N;i++)
    {
        int u,v;
        do
        {
            if(Q.empty())
            {
                puts("NO");
                return 0;
            }
            u=Root(Q.front().first),v=Root(Q.front().second);
            Q.pop();
        }while(u==v);
        if(E[u].size()<E[v].size())
            swap(u,v);
        fa[v]=u;
        Cut(u,v);
        for(auto e:E[v])
        {
            int t=Root(e);
            if(t==u)
                continue;
            Link(t,u);
            Cut(t,v);
        }
    }
    puts("YES");

    return 0;
}
