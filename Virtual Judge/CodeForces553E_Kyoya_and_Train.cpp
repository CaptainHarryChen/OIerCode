#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=52,MAXM=105,MAXT=20005;
const double PI=acos(-1);

struct cpx
{
    double r,i;
    cpx(){}
    cpx(double a,double b):r(a),i(b){}
    cpx operator + (const cpx &t)const
    {return cpx(r+t.r,i+t.i);}
    cpx operator - (const cpx &t)const
    {return cpx(r-t.r,i-t.i);}
    cpx operator * (const cpx &t)const
    {return cpx(r*t.r-i*t.i,r*t.i+t.r*i);}
    cpx operator / (double k)const
    {return cpx(r/k,i/k);}
};

void FFT(cpx A[],int n,int mode)
{
    for(int i=0,j=0;i<n;i++)
    {
        if(i<j)
            swap(A[i],A[j]);
        int k=n>>1;
        while(k&j)
            j^=k,k>>=1;
        j^=k;
    }
    for(int i=1;i<n;i<<=1)
    {
        cpx w1=cpx(cos(PI/i*mode),sin(PI/i*mode)),w;
        for(int j=0;j<n;j+=(i<<1))
        {
            w=cpx(1,0);
            for(int l=j,r=j+i;l<j+i;l++,r++,w=w*w1)
            {
                cpx tmp=A[r]*w;
                A[r]=A[l]-tmp;
                A[l]=A[l]+tmp;
            }
        }
    }
    if(mode==-1)
        for(int i=0;i<n;i++)
            A[i]=A[i]/n;
}

int N,M,T,X;
int E[MAXM][3];
double P[MAXM][MAXT];

int dis[MAXN][MAXN];
double dp[MAXN][MAXT*2],S[MAXM][MAXT*2];

void DP(int L,int mid,int R)
{
    static cpx A[MAXT*10],B[MAXT*10];
    int t=min(T,R-L+1);
    for(int e=1;e<=M;e++)
    {
        int len=1;
        while(len<R-mid+t)
            len<<=1;
        for(int i=0;i<len;i++)
            A[i]=B[i]=cpx(0,0);
        for(int i=0;i<R-mid;i++)
            A[i]=cpx(dp[E[e][1]][R-i],0);
        for(int i=0;i<=t;i++)
            B[i]=cpx(P[e][i],0);
        FFT(A,len,1);
        FFT(B,len,1);
        for(int i=0;i<len;i++)
            A[i]=A[i]*B[i];
        FFT(A,len,-1);
        for(int i=L;i<=mid;i++)
            S[e][i]+=A[R-i].r;
    }
}
void solve(int L,int R)
{
    if(L==R)
    {
        for(int e=1;e<=M;e++)
            dp[E[e][0]][L]=min(dp[E[e][0]][L],S[e][L]+E[e][2]);
        return;
    }
    int mid=(L+R)/2;
    solve(mid+1,R);
    DP(L,mid,R);
    solve(L,mid);
}

int main()
{
    scanf("%d%d%d%d",&N,&M,&T,&X);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
            dis[i][j]=0x3F3F3F3F;
        dis[i][i]=0;
    }
    for(int i=1;i<=M;i++)
    {
        scanf("%d%d%d",&E[i][0],&E[i][1],&E[i][2]);
        dis[E[i][0]][E[i][1]]=min(dis[E[i][0]][E[i][1]],E[i][2]);
        for(int j=1;j<=T;j++)
        {
            scanf("%lf",&P[i][j]);
            P[i][j]/=100000.0;
        }
    }

    for(int k=1;k<=N;k++)
        for(int i=1;i<=N;i++)
            for(int j=1;j<=N;j++)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);

    for(int i=1;i<=N;i++)
        for(int j=0;j<=T;j++)
        {
            dp[i][j]=(i==N?0:1e100);
            dp[i][j+T]=X+dis[i][N];
        }

    DP(0,T,2*T+1);
    solve(0,T);

    printf("%.6f\n",dp[1][0]);

    return 0;
}
