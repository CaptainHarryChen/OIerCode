#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=200005;
int s[MAXN],g[MAXN];
int ans[MAXN];
int ls[MAXN],rs[MAXN];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",s+i,g+i);
	int l=s[1],r=s[1]+g[1];
	ls[1]=l;rs[1]=r;
	for(int i=2;i<=n;i++)
	{
		l=max(l-1,s[i]);
		r=min(r+1,s[i]+g[i]);
		if(l>r)break;
		ls[i]=l;
		rs[i]=r;
	}
	if(l>r)
		puts("-1");
	else
	{
		long long tot=rs[n]-s[n];
		ans[n]=rs[n];
		for(int i=n-1;i>=1;i--)
		{
			if(ls[i]<=ans[i+1]+1&&ans[i+1]+1<=rs[i])
				ans[i]=ans[i+1]+1;
			else if(ls[i]<=ans[i+1]&&ans[i+1]<=rs[i])
				ans[i]=ans[i+1];
			else if(ls[i]<=ans[i+1]-1&&ans[i+1]-1<=rs[i])
				ans[i]=ans[i+1]-1;
			tot+=1LL*(ans[i]-s[i]);
		}
		printf("%I64d\n",tot);
		for(int i=1;i<n;i++)
			printf("%d ",ans[i]);
		printf("%d\n",ans[n]);
	}
	return 0;
}
