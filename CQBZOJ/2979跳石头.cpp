#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define INF 2139062143
#define MAXN 50050
using namespace std;
int n,m,L,Stone[MAXN],stk[MAXN],maxans;
bool DoDP(int ans)
{
	int cnt=0,k=0;
	stk[++k]=0;
	for(int i=1;i<=n;i++)
	{
		if(Stone[i]-Stone[stk[k]]>=ans)
			stk[++k]=i;
		else
			cnt++;
	}
	return cnt<=m;
}
int main()
{
	scanf("%d%d%d",&L,&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&Stone[i]);
	Stone[++n]=L;
	int a=1,b=L,ans;
	while(a<=b)
	{
		ans=(a+b)/2;
		if(DoDP(ans))
		{
			maxans=max(maxans,ans);
			a=ans+1;
		}
		else
			b=ans-1;
	}
	printf("%d\n",maxans);
	return 0;
}
