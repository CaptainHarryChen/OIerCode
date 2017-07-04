#include<cstdio>
#include<algorithm>
using std::sort;
#define MAXN 100005
int n,cnt;
int s[2*MAXN];
int main()
{
	scanf("%d",&n);
	long long ans=0;
	for(int i=1,a1,b1,a2,b2;i<=n;i++)
	{
		scanf("%d%d%d%d",&a1,&b1,&a2,&b2);
		if(a1+b1>=a2+b2)
		{
			s[++cnt]=a1+b1;
			s[++cnt]=a2+b2;
			ans+=(long long)a1+a2;
		}
		else if(a1>b2)ans+=a1-b2;
		else if(a2<b1)ans+=a2-b1;
	}
	sort(s+1,s+cnt+1);
	for(int i=1;i<cnt;i+=2)
		ans-=s[i];
	printf("%I64d\n",ans);
	return 0;
}
