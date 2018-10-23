#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=23;
const double EPS=1e-10;
typedef double Matrix[MAXN*MAXN][MAXN*MAXN];

int dcmp(double a,double b)
{
    if(fabs(a-b)<=EPS)
        return 0;
    return a<b?-1:1;
}

void Gauss(Matrix &A,int n,int m)
{
    for(int r=1,c=1;r<=n&&c<=m;r++,c++)
    {
        int mxr=r;
        for(int i=r+1;i<=n;i++)
            if(dcmp(fabs(A[i][c]),fabs(A[mxr][c]))==1)
                mxr=i;
        if(dcmp(A[mxr][c],0)==0)
        {
            r--;
            continue;
        }
        if(mxr!=r)
            for(int j=1;j<=m+1;j++)
                swap(A[r][j],A[mxr][j]);
        for(int i=1;i<=n;i++)
            if(i!=r&&dcmp(A[i][c],0)!=0)
            {
                double k=A[i][c]/A[r][c];
                for(int j=c;j<=m+1;j++)
                    A[i][j]-=A[r][j]*k;
            }
    }
}

int n,m,A,B;
int ID(int x,int y)
{return (x-1)*n+y;}

bool G[MAXN][MAXN];
int deg[MAXN];
Matrix eq;
double p[MAXN];

int main()
{
    scanf("%d%d%d%d",&n,&m,&A,&B);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        deg[u]++;deg[v]++;
        G[u][v]=G[v][u]=true;
    }
    for(int i=1;i<=n;i++)
        scanf("%lf",&p[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            int x=ID(i,j);
            for(int u=1;u<=n;u++)
                if(G[i][u]&&u!=j)
                    eq[x][ID(u,j)]+=(1-p[u])/deg[u]*p[j];
            for(int v=1;v<=n;v++)
                if(G[j][v]&&i!=v)
                    eq[x][ID(i,v)]+=p[i]*(1-p[v])/deg[v];
            for(int u=1;u<=n;u++)
                if(G[i][u])
                    for(int v=1;v<=n;v++)
                        if(G[j][v]&&u!=v)
                            eq[x][ID(u,v)]+=(1-p[u])/deg[u]*(1-p[v])/deg[v];
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            eq[ID(i,j)][ID(i,j)]+=(i!=j)?p[i]*p[j]-1:-1;
    eq[ID(A,B)][n*n+1]=-1;
/*
    puts("--------------------");
    for(int i=1;i<=n*n;i++)
    {
        for(int j=1;j<=n*n+1;j++)
            printf("%6.2f",eq[i][j]);
        puts("");
    }
    puts("--------------------");
*/
    Gauss(eq,n*n,n*n);
/*
    puts("--------------------");
    for(int i=1;i<=n*n;i++)
    {
        for(int j=1;j<=n*n+1;j++)
            printf("%6.2f",eq[i][j]);
        puts("");
    }
    puts("--------------------");
*/
    for(int i=1;i<=n;i++)
        printf("%.6f\n",eq[ID(i,i)][n*n+1]/eq[ID(i,i)][ID(i,i)]);

    return 0;
}
