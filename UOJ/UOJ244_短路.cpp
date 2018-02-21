#include<iostream>
#include<cstdio>
using namespace std;
#define MAXN 100005
long long A[MAXN],n;
long long dfs(long long now)
{
    if(now==n+1)return A[now];
    long long temp=now+1,ans=0,t;
    bool flag=1;
    while(A[temp]>A[now]&&temp<=n+1)temp++;
    if(temp>n+1)
        flag=0;
    else
    {
        t=0;
        for(long long i=now;i<temp;i++)t+=2*A[i];
        t+=2*A[now]*(temp-now);
        t+=dfs(temp);
        if(t>A[now]*(4*(n+2-now)-3))
            flag=0;
    }
    if(!flag)
        ans+=A[now]*(4*(n+2-now)-3);
    else
        ans+=t;
    return ans;
}
int main()
{
    scanf("%lld",&n);
    for(long long i=n+1;i>0;i--)
        scanf("%lld",&A[i]);
    printf("%lld\n",dfs(1));
    return 0;
}
