#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=10005,MAXM=50005,BLKSIZ=225;

struct Edge
{int u,v;};
struct Query
{
    int l,r,id;
    bool operator < (const Query &t)const
    {return l/BLKSIZ<t.l/BLKSIZ||(l/BLKSIZ==t.l/BLKSIZ&&r<t.r);}
};
struct DSU
{
    int fa[MAXN],dep[MAXN],siz[MAXN];
    pair<int,int> stk[MAXN];
    int tp;
    int ans,cnt;
    int tans,tcnt;

    void Clear(int n)
    {
        fill(fa+1,fa+n+1,0);
        fill(dep+1,dep+n+1,0);
        fill(siz+1,siz+n+1,1);
        tp=0;
        cnt=n;
        ans=n&1;
    }
    int Root(int u)
    {
        int c=0;
        while(fa[u])
            u=fa[u],c++;
        return u;
    }
    void Union(int u,int v,bool flag=false)
    {
        int r1=Root(u),r2=Root(v);
        if(r1==r2)
            return;
        if(dep[r1]<dep[r2])
            swap(r1,r2);
        if(flag)
        {
            if(tp==0)
                tans=ans,tcnt=cnt;
            stk[++tp]=make_pair(r2,fa[r2]);
        }
        ans=ans^siz[r1]^siz[r2]^(siz[r1]+siz[r2]);
        cnt--;
        siz[r1]+=siz[r2];
        fa[r2]=r1;
        if(dep[r1]==dep[r2])
            dep[r1]++;
    }
    void Restore()
    {
        ans=tans,cnt=tcnt;
        while(tp)
        {
            int u=stk[tp].first;
            siz[fa[u]]-=siz[u];
            fa[u]=stk[tp].second;
            tp--;
        }
    }
};

int n,m,q;
Query Q[MAXM];
Edge E[MAXM];
DSU D;
pair<int,int> ans[MAXM];

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&E[i].u,&E[i].v);
    for(int i=1;i<=q;i++)
    {
        scanf("%d%d",&Q[i].l,&Q[i].r);
        Q[i].id=i;
    }
    sort(Q+1,Q+q+1);
    int last=1;
    for(int i=2;i<=q+1;i++)
        if(i==q+1||Q[i].l/BLKSIZ!=Q[last].l/BLKSIZ)
        {
            int j=last,lim=(Q[i].l/BLKSIZ+1)*BLKSIZ;
            D.Clear(n);
            while(j<i&&Q[i].r<lim)
            {
                for(int k=Q[j].l;k<=Q[j].r;k++)
                    D.Union(E[k].u,E[k].v,true);
                ans[Q[j].id]=make_pair(D.cnt,D.ans);
                D.Restore();
                j++;
            }
            int t=lim-1;
            while(j<i)
            {
                while(t<Q[j].r)
                {
                    t++;
                    D.Union(E[t].u,E[t].v,false);
                }
                for(int k=lim;k>=Q[j].l;k--)
                    D.Union(E[k].u,E[k].v,true);
                ans[Q[j].id]=make_pair(D.cnt,D.ans);
                D.Restore();
                j++;
            }
            last=i;
        }
    for(int i=1;i<=q;i++)
        printf("%d %d\n",ans[i].first,ans[i].second);

    return 0;
}
