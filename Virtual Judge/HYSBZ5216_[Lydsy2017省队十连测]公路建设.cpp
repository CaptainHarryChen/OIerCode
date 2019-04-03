#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
const int MAXN=105,MAXM=100005,MAXQ=15005;

struct Edge
{
    int u,v,w;
    Edge(){}
    Edge(int a,int b,int c):u(a),v(b),w(c){}
    bool operator < (const Edge &t)const
    {return w<t.w;}
};
struct DSU
{
    int fa[MAXN];
    void Init()
    {memset(fa,0,sizeof fa);}
    int Root(int x)
    {return fa[x]==0?x:(fa[x]=Root(fa[x]));}
    bool Merge(int x,int y)
    {
        int r1=Root(x),r2=Root(y);
        if(r1==r2)
            return false;
        fa[r1]=r2;
        return true;
    }
};

int n,m,q;
Edge E[MAXM];
vector<int> nd[MAXM*4],ans;
DSU D;

void Merge(const vector<int> &A,const vector<int> &B,vector<int> &C)
{
    D.Init();
    static vector<int> tmp;
    tmp.clear();
    for(vector<int>::const_iterator i=A.begin(),j=B.begin();i!=A.end()||j!=B.end();)
    {
        if(i!=A.end()&&(j==B.end()||E[*i]<E[*j]))
        {
           if(D.Merge(E[*i].u,E[*i].v))
                tmp.push_back(*i);
            i++;
        }
        else
        {
            if(D.Merge(E[*j].u,E[*j].v))
                tmp.push_back(*j);
            j++;
        }
    }
    C.resize(tmp.size());
    copy(tmp.begin(),tmp.end(),C.begin());
}
void Build(int L=1,int R=m,int u=1)
{
    if(L==R)
    {
        nd[u].push_back(L);
        return;
    }
    int mid=(L+R)/2;
    Build(L,mid,u*2);
    Build(mid+1,R,u*2+1);
    Merge(nd[u*2],nd[u*2+1],nd[u]);
}
void Query(int l,int r,int L=1,int R=m,int u=1)
{
    if(l<=L&&R<=r)
    {
        Merge(ans,nd[u],ans);
        return;
    }
    int mid=(L+R)/2;
    if(l<=mid)
        Query(l,r,L,mid,u*2);
    if(mid<r)
        Query(l,r,mid+1,R,u*2+1);
}

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);

    Build();
    while(q--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        ans.clear();
        Query(l,r);
        int val=0;
        for(int i=0;i<(int)ans.size();i++)
            val+=E[ans[i]].w;
        printf("%d\n",val);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}
