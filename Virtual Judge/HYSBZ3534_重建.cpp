#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN=55;
const double EPS=1e-10;

int dcmp(double a,double b)
{
    if(fabs(a-b)<=EPS)
        return 0;
    return a<b?-1:1;
}

int n;
double A[MAXN][MAXN],G[MAXN][MAXN];

double Det(double G[MAXN][MAXN])
{
    bool flag=false;
    for(int r=2,c=2;r<=n;r++,c++)
    {
        int mxr=r;
        for(int i=r+1;i<=n;i++)
            if(dcmp(G[i][c],G[mxr][c])==1)
                mxr=i;
        if(dcmp(G[mxr][c],0)==0)
            return 0;
        if(mxr!=r)
        {
            flag^=1;
            for(int j=1;j<=n;j++)
                swap(G[r][j],G[mxr][j]);
        }
        for(int i=r+1;i<=n;i++)
            if(dcmp(G[i][c],0)!=0)
                for(int j=n;j>=c;j--)
                    G[i][j]-=G[r][j]/G[r][c]*G[i][c];
    }
    double ret=1;
    for(int i=2;i<=n;i++)
        ret*=G[i][i];
    if(flag)
        ret*=-1;
    return ret;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            scanf("%lf",&A[i][j]);
            G[i][i]+=A[i][j]/(1-A[i][j]+EPS);
            G[i][j]-=A[i][j]/(1-A[i][j]+EPS);
        }

    double ans=fabs(Det(G));
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            ans*=(1-A[i][j]+EPS);

    printf("%.13f\n",ans);

    return 0;
}
