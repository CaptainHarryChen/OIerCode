#include<cstdio>
#include<algorithm>
using std::max;
using std::sort;
#define MAXN 1000005
int n,a[MAXN],f[MAXN],s[MAXN];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		f[i]=max(f[i],s[i-a[i]]+1);
		s[i]=max(s[i-1],f[i]);
	}
	printf("%d\n",f[n]);
	return 0;
}
