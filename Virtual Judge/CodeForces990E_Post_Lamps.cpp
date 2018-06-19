#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1000005;

int n,m,k;
bool s[MAXN];
int val[MAXN],last[MAXN];

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	int mx=0;
	for(int i=1,x;i<=m;i++)
	{
		scanf("%d",&x);
		s[x]=true;
		if(s[x-1])
			last[x]=last[x-1];
		else
			last[x]=x-1;
		mx=max(mx,x-last[x]);
	}
	if(s[0]||mx+1>k)
	{
		puts("-1");
		return 0;
	}
	for(int i=1;i<=k;i++)
		scanf("%d",&val[i]);
	
	long long ans=0x7FFFFFFFFFFFFFFFLL;
	for(int i=mx+1;i<=k;i++)
	{
		int step=0;
		for(int j=0;j<n;j+=i)
		{
			if(s[j])
				j=last[j];
			step++;
		}
		ans=min(ans,1LL*step*val[i]);
	}
	printf("%I64d\n",ans);
	
	return 0;
}
