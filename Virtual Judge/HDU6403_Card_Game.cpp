#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=200005,MOD=998244353;

struct Edge
{
    int v,id;
    Edge()=default;
    Edge(int _v,int _id)
    {v=_v;id=_id;}
};

int n,m;
vector<Edge> adj[MAXN];
bool vis[MAXN],visE[MAXN];
vector<Edge> circle;
int dcnt[MAXN],rdcnt[MAXN];
bool iscircle[MAXN];
Edge stk[MAXN];
int top;

int FindCircle(int u,int fa=0)
{
    vis[u]=true;
    int ans=0;
    for(const auto &e:adj[u])
        if(e.id!=fa&&!visE[abs(e.id)])
        {
            visE[abs(e.id)]=true;
            if(vis[e.v])
            {
                if(!circle.empty())
                    return -1;
                ans=1;
                int id=top;
                while(stk[id].v!=e.v&&id>0)
                    id--;
                while(id<=top&&id>0)
                    circle.push_back(stk[id++]);
                circle.push_back(Edge(u,e.id));
            }
            else
            {
                stk[++top]=Edge(u,e.id);
                ans|=FindCircle(e.v,-e.id);
                top--;
            }
        }
    return ans;
}

void dfs(int u,int fa=0)
{
    dcnt[u]=0;
    for(const auto &e:adj[u])
        if(e.id!=fa&&!iscircle[e.v])
        {
            dfs(e.v,-e.id);
            dcnt[u]+=dcnt[e.v]+(e.id<0);
        }
}
int tmin,tcnt;
void rdfs(int u,int fa=0,int cnt=0)
{
    rdcnt[u]=cnt;
    if(tmin==rdcnt[u]+dcnt[u])
        tcnt++;
    if(tmin>rdcnt[u]+dcnt[u])
    {
        tmin=rdcnt[u]+dcnt[u];
        tcnt=1;
    }
    for(const auto &e:adj[u])
        if(e.id!=fa)
            cnt+=dcnt[e.v]+(e.id<0);
    for(const auto &e:adj[u])
        if(e.id!=fa)
            rdfs(e.v,-e.id,cnt-(dcnt[e.v]+(e.id<0))+(e.id>0));
}

pair<int,int> solve(int u)
{
    pair<int,int> ans(0,0);
    top=0;
    circle.clear();
    int type=FindCircle(u);
    if(type==-1)
        return make_pair(-1,-1);
    if(type)
    {
        int cnt=0;
        for(const auto &e:circle)
        {
            iscircle[e.v]=true;
            cnt+=(e.id>0);
        }
        ans.first+=min(cnt,(int)circle.size()-cnt);
        for(const auto &e:circle)
        {
            dfs(e.v);
            ans.first+=dcnt[e.v];
        }
        if(cnt==(int)circle.size()-cnt)
            ans.second=2;
        else
            ans.second=1;
    }
    else
    {
        dfs(u);
        tmin=0x7FFFFFFF,tcnt=0;
        rdfs(u);
        ans.first=tmin;
        ans.second=tcnt;
    }
    return ans;
}

int main()
{
    int T;
    scanf("%d",&T);
    for(int test=1;test<=T;test++)
    {
        scanf("%d",&n);
        for(int i=1;i<=n*2;i++)
        {
            adj[i].clear();
            vis[i]=false;
            iscircle[i]=false;
            visE[i]=false;
        }
        for(int i=1,x,y;i<=n;i++)
        {
            scanf("%d%d",&x,&y);
            adj[y].push_back(Edge(x,i));
            if(x!=y)
                adj[x].push_back(Edge(y,-i));
        }
        for(int i=1;i<=n*2;i++)
            sort(adj[i].begin(),adj[i].end(),[](const Edge &a,const Edge &b) {return a.id>b.id;});

        pair<int,int> ans(0,1);
        for(int i=1;i<=n*2;i++)
            if(!vis[i])
            {
                auto tmp=solve(i);
                if(tmp.first==-1&&tmp.second==-1)
                {
                    ans=tmp;
                    break;
                }
                ans.first+=tmp.first;
                ans.second=1LL*ans.second*tmp.second%MOD;
            }

        printf("%d %d\n",ans.first,ans.second);
    }

    return 0;
}
