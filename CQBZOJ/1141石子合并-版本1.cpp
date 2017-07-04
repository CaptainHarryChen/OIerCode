#include<iostream>
#include<cstring>
using namespace std;
#define MAXN 105
int N,num[MAXN],dp[MAXN][MAXN],sum[MAXN],path[MAXN][MAXN];
void print_ans(int x,int y)
{
    if(x==y)
    {
        cout<<num[x];
        return;
    }
    cout<<'(';
    print_ans(x,path[x][y]);
    cout<<")(";
    print_ans(path[x][y]+1,y);
    cout<<')';
}
int main()
{
    cin>>N;
    memset(dp,127,sizeof dp);
    for(int i=1;i<=N;i++)
    {
        cin>>num[i];
        dp[i][i]=num[i];
        sum[i]=sum[i-1]+num[i];
    }
    for(int l=1;l<=N;l++)
        for(int i=1,j=i+l;j<=N;i++,j++)
            for(int k=i;k<=j;k++)
                if(dp[i][j]>dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1])
                {
                    dp[i][j]=dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1];
                    path[i][j]=k;
                }
    cout<<dp[1][N]-sum[N]<<endl;
    print_ans(1,N);
    cout<<endl;
    return 0;
}
