#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=200005;

int n,m;
int a[MAXN],b[MAXN];

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	for(int i=1;i<=m;i++)
		scanf("%d",b+i);
	sort(a+1,a+n+1);
	for(int i=1;i<=m;i++)
		printf("%d ",upper_bound(a+1,a+n+1,b[i])-a-1);
	puts("");
	
	return 0;
}
