#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=20005,MAXM=100005;

struct Edge
{
    int u,v,d;
    Edge(){}
    Edge(int _u,int _v,int _d)
    {u=_u;v=_v;d=_d;}

    bool operator < (const Edge &t)const
    {return d<t.d;}
};

int fa[MAXN];
int Root(int x)
{
    if(fa[x]==0)
        return x;
    return fa[x]=Root(fa[x]);
}

int N,M,K;
Edge E[MAXM];

bool used[MAXM],ans[MAXM];

int main()
{
    scanf("%d%d%d",&N,&M,&K);
    for(int i=1;i<=M;i++)
        scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].d);
    sort(E+1,E+M+1);

    for(int i=M;i>=1;i--)
    {
        int r1=Root(E[i].u),r2=Root(E[i].v);
        if(r1==r2)
            continue;
        fa[r1]=r2;
        used[i]=true;
    }

    int cnt=0;
    for(int i=1;i<=M&&E[i].d==0;i++)
        cnt+=used[i];
    if(cnt>K)
    {
        puts("no solution");
        return 0;
    }
    cnt=0;
    memset(fa,0,sizeof fa);
    for(int i=1;i<=M&&E[i].d==0&&cnt<K;i++)
        if(used[i])
        {
            int r1=Root(E[i].u),r2=Root(E[i].v);
            fa[r1]=r2;
            cnt++;
            ans[i]=true;
        }
    for(int i=1;i<=M;i++)
    {
        int r1=Root(E[i].u),r2=Root(E[i].v);
        if(r1==r2||(cnt==K&&E[i].d==0))
            continue;
        fa[r1]=r2;
        ans[i]=true;
        cnt++;
    }
    if(cnt!=N-1)
    {
        puts("no solution");
        return 0;
    }
    for(int i=1;i<=M;i++)
        if(ans[i])
            printf("%d %d %d\n",E[i].u,E[i].v,E[i].d);

    return 0;
}
