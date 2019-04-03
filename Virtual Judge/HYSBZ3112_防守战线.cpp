#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=1005,MAXM=10005;
const double EPS=1e-8;

int dcmp(double a,double b)
{
    if(fabs(a-b)<=EPS)
        return 0;
    return a<b?-1:1;
}

int n,m;
double A[MAXN][MAXM];

void pivot(int r,int c)
{
    double tmp=-A[r][c];
    A[r][c]=-1;
    for(int j=0;j<=m;j++)
        A[r][j]/=tmp;
    for(int i=0;i<=n;i++)
        if(i!=r&&dcmp(A[i][c],0)!=0)
        {
            tmp=A[i][c];
            A[i][c]=0;
            for(int j=0;j<=m;j++)
                A[i][j]+=tmp*A[r][j];
        }
}
double simplex()
{
    for(;;)
    {
        int i=0,j=0;
        double mn=1e10,mx=0;
        for(int k=1;k<=m;k++)
            if(dcmp(A[0][k],mx)==1)
            {mx=A[0][k];j=k;}
        if(j==0)
            break;
        for(int k=1;k<=n;k++)
            if(dcmp(A[k][j],0)==-1&&dcmp(-A[k][0]/A[k][j],mn)==-1)
                mn=-A[k][0]/A[k][j],i=k;
        if(i==0)
            return -1;
        pivot(i,j);
    }
    return A[0][0];
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%lf",&A[i][0]);
    for(int i=1;i<=m;i++)
    {
        int l,r,d;
        scanf("%d%d%d",&l,&r,&d);
        for(int j=l;j<=r;j++)
            A[j][i]=-1;
        A[0][i]=d;
    }
    printf("%.0f\n",simplex());

    return 0;
}
