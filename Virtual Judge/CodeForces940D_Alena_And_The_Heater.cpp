#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005,INF=1000000000;

int n,l1=-INF,l2=INF,r1=-INF,r2=INF;
int a[MAXN],b[MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	for(int i=1;i<=n;i++)
		scanf("%1d",b+i);
	int cnt[2]={4,0};
	for(int i=5;i<=n;i++)
	{
		int mx=-INF,mn=INF;
		for(int j=i-4;j<=i;j++)
		{
			mx=max(mx,a[j]);
			mn=min(mn,a[j]);
		}
		if(cnt[0]==4)
		{
			if(b[i]==0)
				l2=min(l2,mx);
			else
				l1=max(l1,mx+1);
		}
		else if(cnt[1]==4)
		{
			if(b[i]==0)
				r2=min(r2,mn-1);
			else
				r1=max(r1,mn);
		}
		cnt[b[i-4]]--;
		cnt[b[i]]++;
	}
	printf("%d %d\n",l1,r2);
	
	return 0;
}
