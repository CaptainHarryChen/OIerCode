#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
using namespace std;
const int MAXN=105,MAXM=1005;

struct Edge
{
    int u,v,d;
    Edge(){}
    Edge(int _u,int _v,int _d)
    {u=_u;v=_v;d=_d;}

    bool operator < (const Edge &t)const
    {return d<t.d;}
};

struct DSU
{
    int fa[MAXN];
    void Clear()
    {memset(fa,0,sizeof fa);}
    int Root(int x)
    {
        if(fa[x]==0)
            return x;
        return fa[x]=Root(fa[x]);
    }
    void Union(int x,int y)
    {
        int r1=Root(x),r2=Root(y);
        if(r1!=r2)
            fa[r1]=r2;
    }
};

int N,M;
Edge E[MAXM];
DSU D,tmp;
map<int,int> val;

int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=M;i++)
        scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].d);

    sort(E+1,E+M+1);
    int c=0;
    for(int i=1;i<=M;i++)
    {
         int r1=D.Root(E[i].u),r2=D.Root(E[i].v);
        if(r1==r2)
            continue;
        D.Union(r1,r2);
        val[E[i].d]++;
        c++;
    }
    if(c<N-1)
    {
        puts("0");
        return 0;
    }

    tmp.Clear();
    int last=1,ans=1;
    for(int i=2;i<=M+1;i++)
        if(E[i].d!=E[i-1].d)
        {
            int len=i-last,cnt=0,v=val[E[last].d];
            if(v>0)
            {
                for(int s=1;s<(1<<len);s++)
                    if(__builtin_popcount(s)==v)
                    {
                        D=tmp;
                        bool flag=true;
                        for(int j=last;j<i&&flag;j++)
                            if(s&(1<<(j-last)))
                            {
                                int r1=D.Root(E[j].u),r2=D.Root(E[j].v);
                                if(r1==r2)
                                    flag=false;
                                else
                                    D.Union(r1,r2);
                            }
                        cnt+=flag;
                    }
                ans=ans*cnt%31011;
            }
            for(int j=last;j<i;j++)
            {
                int r1=tmp.Root(E[j].u),r2=tmp.Root(E[j].v);
                if(r1==r2)
                    continue;
                tmp.Union(r1,r2);
            }
            last=i;
        }
    printf("%d\n",ans);

    return 0;
}
