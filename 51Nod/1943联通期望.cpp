#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=16,MAXM=MAXN*MAXN,MAXS=(1<<14)+10;

struct Edge
{
    int u,v,w,id;
    double p;
    bool operator < (const Edge &t)const
    {return w<t.w||(w==t.w&&id<t.id);}
};

int n,m;
Edge E[MAXM];
double f[MAXM][MAXS],h[MAXS],ans;

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d%lf",&E[i].u,&E[i].v,&E[i].w,&E[i].p);
        E[i].id=i;
    }
    sort(E+1,E+m+1);

    for(int i=0;i<n;i++)
        f[0][1<<i]=1;
    for(int s=0;s<(1<<n);s++)
        h[s]=1;

    for(int i=0;i<m;i++)
    {
        int u=E[i+1].u-1,v=E[i+1].v-1;
        for(int s=0;s<(1<<n);s++)
        {
            if((s>>u&1)==(s>>v&1))
                f[i+1][s]+=f[i][s];
            else
            {
                f[i+1][s]+=f[i][s]*E[i+1].p;
                if((s>>u&1)==1)
                {
                    for(int rs=((1<<n)-1)^s,t=rs;t;t=(t-1)&rs)
                        if(t>>v&1)
                            f[i+1][s|t]+=f[i][s]*f[i][t]*(1-E[i+1].p)/h[s|t]*h[s]*h[t];
                }
            }
        }
        {
            for(int s=0;s<(1<<n);s++)
                if(s>>u&1)
                    for(int rs=((1<<n)-1)^s,t=rs;t;t=(t-1)&rs)
                        if(t>>v&1)
                            ans+=E[i+1].w*(1-E[i+1].p)*f[i][s]*f[i][t]/h[s|t]*h[s]*h[t];
        }
        for(int s=0;s<(1<<n);s++)
            if((s>>u&1)==1&&(s>>v&1)==1)
                h[s]*=E[i+1].p;
    }

    printf("%.6f\n",ans);

    return 0;
}
