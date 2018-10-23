#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=11,MOD=1000000000;
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
typedef int Matrix[MAXN*MAXN][MAXN*MAXN];

int Det(Matrix &A,int n)
{
    bool flag=0;
    for(int r=1,c=1;r<=n&&c<=n;r++,c++)
    {
        int mxr=r;
        while(A[mxr][c]==0&&mxr<=n)
            mxr++;
        if(mxr>n)
            return 0;
        if(mxr!=r)
        {
            for(int j=1;j<=n;j++)
                swap(A[mxr][j],A[r][j]);
            flag^=1;
        }
        for(int i=r+1;i<=n;i++)
            while(A[i][c])
            {
                int k=A[i][c]/A[r][c];
                for(int j=c;j<=n;j++)
                    A[i][j]=(A[i][j]-1LL*k*A[r][j]%MOD+MOD)%MOD;
                if(A[i][c]==0)
                   break;
                for(int j=1;j<=n;j++)
                    swap(A[r][j],A[i][j]);
                flag^=1;
            }
    }
    int res=1;
    for(int i=1;i<=n;i++)
        res=1LL*res*A[i][i]%MOD;
    if(flag)
        res=(MOD-res)%MOD;
    return res;
}

int n,m;
char mp[MAXN][MAXN];
int id[MAXN][MAXN];

Matrix A;

int main()
{
    scanf("%d%d",&n,&m);
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",mp[i]+1);
        for(int j=1;j<=m;j++)
            if(mp[i][j]=='.')
                id[i][j]=++cnt;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(mp[i][j]=='.')
                for(int d=0;d<4;d++)
                {
                    int x=i+dir[d][0],y=j+dir[d][1];
                    if(x>0&&y>0&&x<=n&&y<=m&&mp[x][y]=='.')
                    {
                        A[id[i][j]][id[x][y]]--;
                        A[id[i][j]][id[i][j]]++;
                    }
                }

    printf("%d\n",Det(A,cnt-1));

    return 0;
}
