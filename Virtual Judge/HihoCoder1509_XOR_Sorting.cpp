#include<cstdio>
#include<cstring>
const int MAXN=65;

long long a[MAXN];
int state[MAXN];

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",a+i);
	memset(state,-1,sizeof state);
	int ans=60;
	for(int i=1;i<n;i++)
	{
		if(a[i]==a[i+1])
		{ans=-1;break;}
		int j=59;
		while((a[i]&(1LL<<j))==(a[i+1]&(1LL<<j)))
			j--;
		if(a[i]>a[i+1])
		{
			if(state[j]==0)
			{ans=-1;break;}
			if(state[j]==-1)
				ans--;
			state[j]=1;
		}
		else
		{
			if(state[j]==1)
			{ans=-1;break;}
			if(state[j]==-1)
				ans--;
			state[j]=0;
		}
	}
	if(ans==-1)
		puts("0");
	else
		printf("%lld\n",1LL<<ans);
	return 0;
}
