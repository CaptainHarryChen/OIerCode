#include<cstdio>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
const int MAXN=100005;

class BIT
{
    int sum[MAXN],vis[MAXN],ti;
    void Update(int pos)
    {
        if(vis[pos]!=ti)
        {
            sum[pos]=0;
            vis[pos]=ti;
        }
    }
public:
    BIT(){ti=0;}
    void Clear(){ti++;}
    void Add(int pos,int val)
    {
        while(pos<MAXN)
        {
            Update(pos);
            sum[pos]+=val;
            pos+=pos&(-pos);
        }
    }
    int Query(int pos)
    {
        int res=0;
        while(pos)
        {
            Update(pos);
            res+=sum[pos];
            pos-=pos&(-pos);
        }
        return res;
    }
};

int N,C[MAXN],A[MAXN],B[MAXN];

int fa[MAXN],siz[MAXN];
vector<int> son[MAXN];

int tp[MAXN],dep[MAXN];

void dfs1(int u)
{
    siz[u]=1;
    for(int i=0;i<(int)son[u].size();i++)
    {
        int v=son[u][i];
        fa[v]=u;
        dfs1(v);
        siz[u]+=siz[v];
    }
}
void dfs2(int u)
{
    int best=0,mx=0;
    for(int i=0;i<(int)son[u].size();i++)
    {
        int v=son[u][i];
        if(mx<siz[v])
        {
            best=v;
            mx=siz[v];
        }
    }
    if(best==0)
        return;
    for(int i=0;i<(int)son[u].size();i++)
    {
        int v=son[u][i];
        if(v==best)
        {
            tp[v]=tp[u];
            dep[v]=dep[u]+1;
        }
        else
        {
            tp[v]=v;
            dep[v]=0;
        }
        dfs2(v);
    }
}

stack<pair<int,int> > stk[MAXN];
BIT cnt;
pair<int,int> arr[MAXN],tmp[MAXN];
int tot,tot2;
int val[MAXN];

long long Calc_inv()
{
    cnt.Clear();
    for(int i=1;i<=tot;i++)
        val[i]=arr[i].first;
    sort(val+1,val+tot+1);
    int m=unique(val+1,val+tot+1)-val-1;
    for(int i=1;i<=tot;i++)
        arr[i].first=lower_bound(val+1,val+m+1,arr[i].first)-val;
    long long res=0;
    for(int i=1;i<=tot;i++)
    {
        res+=1LL*cnt.Query(arr[i].first-1)*arr[i].second;
        cnt.Add(arr[i].first,arr[i].second);
    }
    return res;
}

int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
        scanf("%d",&C[i]);
    for(int i=1;i<N;i++)
    {
        scanf("%d%d",&A[i],&B[i]);
        son[A[i]].push_back(B[i]);
    }

    dfs1(1);
    tp[1]=1;
    dfs2(1);

    stk[1].push(make_pair(0,C[1]));
    for(int i=1;i<N;i++)
    {
        int u=B[i],c=C[B[i]];
        tot=0;
        while(u)
        {
            int d=dep[u],last=-1;
            u=tp[u];
            tot2=0;
            while(!stk[u].empty()&&stk[u].top().first<=d)
            {
                tmp[++tot2]=make_pair(stk[u].top().second,stk[u].top().first-last);
                last=stk[u].top().first;
                stk[u].pop();
            }
            if(!stk[u].empty())
                tmp[++tot2]=make_pair(stk[u].top().second,d-last);
            stk[u].push(make_pair(d,c));
            while(tot2)
                arr[++tot]=tmp[tot2--];
            u=fa[u];
        }
        printf("%lld\n",Calc_inv());
    }

    return 0;
}
