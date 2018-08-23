#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;
const int MAXN=10005;

int N,K;
int A[MAXN];
vector<int> blk;
int a,b;

int solve(int k)
{
    int sum=0;
    for(int i=0;k>0&&i<(int)blk.size();i++)
    {
        sum+=blk[i];
        k-=2;
    }
    return sum;
}
int solve2(int k)
{
    int sum=0;
    for(int i=0;k>=2&&i<(int)blk.size();i++)
    {
        sum+=blk[i];
        k-=2;
    }
    return sum;
}

int main()
{
    while(scanf("%d%d",&N,&K)!=EOF)
    {
        for(int i=1;i<=N;i++)
            scanf("%1d",&A[i]);
        blk.clear();
        a=b=0;
        for(int i=1,j;i<=N;i++)
            if(A[i]==1)
            {
                for(j=i;j<=N&&A[j]==1;j++);
                if(i==1)a=j-i;
                else if(j==N+1)b=j-i;
                else
                    blk.push_back(j-i);
                i=j-1;
            }
        sort(blk.begin(),blk.end(),greater<int>());
        int ans=solve(K);
        if(a)ans=max(ans,solve2(K)+a);
        if(a&&b&&K>=1)ans=max(ans,solve2(K-1)+a+b);
        if(a&&K>=1)ans=max(ans,solve(K-1)+a);
        if(b&&K>=1)ans=max(ans,solve(K-1)+b);
        if(a&&b&&K>=2)ans=max(ans,solve(K-2)+a+b);
        
        printf("%d\n",ans);
    }
    
    return 0;
}
