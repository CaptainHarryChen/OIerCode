#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int n;
int a[MAXN],b[MAXN],pos[MAXN];
bool vis[MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",a+i);
		pos[a[i]]=i;
	}
	sort(a+1,a+n+1);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		if(vis[a[i]]||pos[a[i]]==i)
			continue;
		int cnt=0;
		for(int j=i;!vis[a[j]];j=pos[a[j]])
		{
			vis[a[j]]=true;
			cnt++;
			ans+=a[j];
		}
		ans-=a[i];
		ans+=min(a[i]*(cnt-1),(a[1]+a[i])*2+a[1]*(cnt-1));
	}
	printf("%d\n",ans);
	
	return 0;
}
