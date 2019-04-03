#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=305,MAXM=1005;
const double EPS=1e-8;

int dcmp(double a,double b)
{
    if(fabs(a-b)<=EPS)
        return 0;
    return a<b?-1:1;
}

struct Edge
{
    int u,v,w,f,a,b,id;
    Edge(){}
    Edge(int _u,int _v,int _w,int _f,int _a,int _b,int _id):u(_u),v(_v),w(_w),f(_f),a(_a),b(_b),id(_id){}
};

int n,m,R,C;
vector<Edge> adj[MAXN];
Edge E[MAXM];

double A[MAXM][MAXM*4];

void pivot(int r,int c)
{
    double tmp=-A[r][c];
    A[r][c]=-1;
    for(int j=0;j<=C;j++)
        A[r][j]/=tmp;
    for(int i=0;i<=R;i++)
        if(dcmp(A[i][c],0)!=0&&i!=r)
        {
            tmp=A[i][c];
            A[i][c]=0;
            for(int j=0;j<=C;j++)
                A[i][j]+=tmp*A[r][j];
        }
}

double solve()
{
    for(;;)
    {
        int i=0,j=0;
        double mx=0,mn=1e10;
        for(int k=1;k<=C;k++)
            if(dcmp(A[0][k],mx)==1)
                mx=A[0][k],j=k;
        if(j==0)
            break;
        for(int k=1;k<=R;k++)
            if(dcmp(A[k][j],0)==-1&&dcmp(-A[k][0]/A[k][j],mn)==-1)
                mn=-A[k][0]/A[k][j],i=k;
        if(i==0)
            return -1;
        pivot(i,j);
    }
    return A[0][0];
}

int stk[MAXN],tp;
bool dfs(int u,int T,int i,int pre=0)
{
    if(u==T)
    {
        while(tp)
        {
            int j=stk[tp];
            C++;
            A[i][C]=-1;A[j][C]=-1;
            A[0][C]=E[j].w-E[i].w;
            tp--;
        }
        return true;
    }
    for(int j=0;j<(int)adj[u].size();j++)
    {
        int v=adj[u][j].v;
        if(v==pre)
            continue;
        stk[++tp]=adj[u][j].id;
        if(dfs(v,T,i,u))
            return true;
        tp--;
    }
    return false;
}

int main()
{
    scanf("%d%d",&n,&m);
    R=m;
    for(int i=1,u,v,w,f,a,b;i<=m;i++)
    {
        scanf("%d%d%d%d%d%d",&u,&v,&w,&f,&a,&b);
        E[i]=Edge(u,v,w,f,a,b,i);
        if(f)
        {
            adj[u].push_back(Edge(u,v,w,f,a,b,i));
            adj[v].push_back(Edge(v,u,w,f,a,b,i));
            A[i][0]=b;
        }
        else
            A[i][0]=a;
    }
    for(int i=1;i<=m;i++)
        if(E[i].f==0)
        {
            tp=0;
            dfs(E[i].u,E[i].v,E[i].id);
        }
/*
    for(int j=0;j<=C;j++)
    {
        for(int i=0;i<=R;i++)
            printf("%.0f ",A[i][j]);
        puts("");
    }
*/
    printf("%.0f\n",solve());

    return 0;
}
