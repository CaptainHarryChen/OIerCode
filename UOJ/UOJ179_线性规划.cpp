#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=55;
const double EPS=1e-8;

int dcmp(double a,double b)
{
    if(fabs(a-b)<=EPS)
        return 0;
    return a<b?-1:1;
}

int n,m,type;
double A[MAXN][MAXN];
int id[MAXN],tp[MAXN];

void pivot(int r,int c)
{
    swap(id[r+n],id[c]);
    double tmp=-A[r][c];
    A[r][c]=-1;
    for(int j=0;j<=n;j++)
        A[r][j]/=tmp;
    for(int i=0;i<=m;i++)
        if(i!=r&&dcmp(A[i][c],0)!=0)
        {
            tmp=A[i][c];
            A[i][c]=0;
            for(int j=0;j<=n;j++)
                A[i][j]+=tmp*A[r][j];
        }
}

void solve()
{
    for(int i=1;i<=n;i++)
        id[i]=i;
    for(;;)
    {
        double mn=0;
        int i=0,j=0;
        for(int k=1;k<=m;k++)
            if(dcmp(A[k][0],mn)==-1)
                mn=A[k][0],i=k;
        if(i==0)
            break;
        for(int k=1;k<=n;k++)
            if(dcmp(A[i][k],0)==1)
            {j=k;break;}
        if(j==0)
        {
            puts("Infeasible");
            return;
        }
        pivot(i,j);
    }
    for(;;)
    {
        int i=0,j=0;
        double mx=0,mn=1e9;
        for(int k=1;k<=n;k++)
            if(dcmp(A[0][k],mx)==1)
                mx=A[0][k],j=k;
        if(j==0)
            break;
        for(int k=1;k<=m;k++)
            if(dcmp(A[k][j],0)==-1&&dcmp(-A[k][0]/A[k][j],mn)==-1)
                mn=-A[k][0]/A[k][j],i=k;
        if(i==0)
        {
            puts("Unbounded");
            return;
        }
        pivot(i,j);
    }
    printf("%.9f\n",A[0][0]);
    for(int i=n+1;i<=n+m;i++)
        tp[id[i]]=i-n;
    if(type)
        for(int i=1;i<=n;i++)
            printf("%.9f%c",tp[i]?A[tp[i]][0]:0," \n"[i==n]);
}

int main()
{
    scanf("%d%d%d",&n,&m,&type);
    for(int i=1;i<=n;i++)
        scanf("%lf",&A[0][i]);
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            scanf("%lf",&A[i][j]);
            A[i][j]*=-1;
        }
        scanf("%lf",&A[i][0]);
    }

    solve();

    return 0;
}
