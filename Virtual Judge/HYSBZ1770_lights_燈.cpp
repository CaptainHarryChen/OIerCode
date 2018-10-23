#include<cstdio>
#include<bitset>
#include<algorithm>
using namespace std;
const int MAXN=40;
typedef bitset<MAXN> Matrix[MAXN];

void Gauss(Matrix &eq,int n,int m)
{
    int r,c;
    for(r=1,c=1;r<=n&&c<=m;r++,c++)
    {
        int mxr=r;
        while(eq[mxr][c]==0&&mxr<n)
            mxr++;
        if(eq[mxr][c]==0)
            continue;
        if(mxr!=r)
            swap(eq[mxr],eq[r]);
        for(int i=1;i<=n;i++)
            if(i!=r&&eq[i][c])
                eq[i]^=eq[r];
    }
}

int n,m;
int ans=0x3F3F3F3F;
bitset<MAXN> x;
Matrix eq;

void dfs(int i,int now=0)
{
    if(now>=ans)
        return;
    if(i==0)
    {
        ans=now;
        return;
    }
    if(eq[i][i])
    {
        int t=eq[i][n+1];
        for(int j=i+1;j<=n;j++)
            if(eq[i][j])
                t^=x[j];
        x[i]=t;
        dfs(i-1,now+t);
    }
    else
    {
        x[i]=0;
        dfs(i-1,now);
        x[i]=1;
        dfs(i-1,now+1);
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        eq[u][v]=eq[v][u]=1;
    }
    for(int i=1;i<=n;i++)
        eq[i][i]=eq[i][n+1]=1;
    Gauss(eq,n,n);
    dfs(n);
    printf("%d\n",ans);

    return 0;
}
