#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=105;

int n,d;
int a[MAXN];

int main()
{
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	sort(a+1,a+n+1);
	int ans=n-1;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			if(a[j]-a[i]<=d)
				ans=min(ans,i-1+n-j);
	printf("%d\n",ans);
	return 0;
}
